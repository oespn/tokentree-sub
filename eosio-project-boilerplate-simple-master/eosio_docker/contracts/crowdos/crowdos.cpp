#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;


class crowdos : public eosio::contract {
  public:
    // a crowdos begins with a company posting a listing
    // the company creates the listing with title, description and the offervalue (in CRWD), target (max checks)
    // contract has an expiry data and quota (target)

    //** expansion: the crowdos would originate from a greater company subscription/ monthly budget 
    // the subscription contains: 
    // - primary contact
    // - processes
    // - article type
    // - terms and conditions  

    // once created a checker can take on the offer for it's value
    // a % of the offer is set aside for validators
    // the checkers record a vote (& comment)
    // validations are required when a fail is reported.  
    // validators are checkers that voted the contract as a 'pass', 
    // validators are given the opportunity to earn back their staked amount by validating the fail.

    // payout checks that at least 'check_count' validations have been done 

    // What next?
    // Implement database as mongodb. Store hashes of records to the blockchain

    crowdos(account_name s):
        contract(s), // initialization of the base class for the contract
        _listings(s, s), // initialize the table with code and scope NB! Look up definition of code and scope
        _checks(s,s),
        _validations(s, s)
    {
    }

    /// @abi action
    void addlisting(account_name username, const std::string& title, uint32_t target, const std::string& description, uint64_t offervalue, time expires) {
        require_auth(username); // this user is a company
        // Let's make sure the primary key doesn't exist
        eosio_assert(_listings.find(title) == _listings.end(), "This listing already exists");
        //** future: charge the sender rather than self 
        
        _listings.emplace(get_self(), [&]( auto& p ) {
            p.company = username;
            p.title = title,
            p.target = target;
            p.description = description;
            p.offervalue = offervalue;
            p.expires = expires;
        });
    } 

    /// @abi action
    void check(account_name username, double geo, double listingkey, time checked) {
        // usage: assume caller is the Checker
        require_auth(username); // this user is a checker
        // Let's make sure the primary key doesn't exist
        eosio_assert(_checks.find(listingkey+username) == _checks.end(), "you can only check once ;)");
        
        //get from listingkey
        auto listing = _listings.find(listingkey);

        eosio_assert(listing->checkcount < listing->target, "Too slow, the quota has already been met.");

        time now = current_time();
        eosio_assert(listing->expires > now, "You cannot check on an expired listing");

        _checks.emplace(get_self(), [&]( auto& p ) {
            p.checker = username;
            p.company = listing->company;
            p.listingkey = listingkey;         
            p.checked = checked;
        });

        if (listing != _listings.end())
        {
            _listings.modify(listing, get_self(), [&](auto& p)
                                        {
                                            p.checkcount = p.checkcount + 1;
                                        });
        }
    } 

    /// @abi action
    void validate(account_name username, uint64_t checkkey, time validated, std::string comment, bool vote) {
        require_auth(username); // this user is a validator
        // Let's make sure the primary key doesn't exist

        auto check = _checks.find(checkkey);
        auto listing = _listings.find(check->listingkey);

        //** solve best way to check uniqueness on a multi-primarykey 
        eosio_assert(_validations.by_validatorkey(checkkey, username).end(), "The validation of this check already exists");
        // assert offer hasn't expired 
        time now = current_time();
        eosio_assert(listing->expires > now, "You cannot validate a listing for an expired offer");

        _validations.emplace(get_self(), [&]( auto& p ) {  
            p.checkkey = checkkey;
            p.listingkey = listingkey;
            p.validator = username; // the user who validated primary key
            p.when = validated;
            p.datetimestamp = validated; // as epoch
            p.comment = comment;
            p.vote = vote;
        });

        if (listing != _listings.end())
        {
            _listings.modify(listing, get_self(), [&](auto& p)
                                        {
                                            p.validatecount = p.validatecount + 1;
                                        });
        }
    } 


    /// @abi action
    void payout(account_name username, double listingkey, time closed) {
        require_auth(username); // this user is a validator
        // Let's make sure the primary key doesn't exist
        
        auto listing = _listings.find(listingkey);
        if (listing != _listings.end())
        {
            _listings.modify(listing, get_self(), [&](auto& p)
                                        {
                                            p.closed = closed;
                                        });
        }

        auto checkertokens = listing->offervalue/2;
        // half of tokens go to the checkers 
        //** future: check that they have at least 3 verifications by other parties
        auto checkerpay = checkertokens / listing.validatecount;
        std::vector<double> checksForModify;
          // find all checks
          for(auto& item : _checks)
          {
              if (item.geo == listingkey)
              {
                  checksForModify.push_back(item.geo);   
              }
          }
          // update the paid out tokens to each checker
          for (double key : checksForModify)
          {
              //seek the checker & payout
          }

        // balance divided by the verifiers 
        auto verifiertokens = listing->offervalue - checkerpay; 
        auto verifierpay = verifiertokens / listing.validatecount;
        
          // find all verifiers
          std::vector<double> keysForModify;
          for(auto& item : _validations)
          {
              if (item.listingkey == listingkey)
              {
                  keysForModify.push_back(item.listingkey);   
              }
          }
          // update the paid out tokens to each checker
          for (double key : keysForModify)
          {
              //seek the validator & payout
          }

        // for each associated validation - pay out the share of the tokens
        
        //** action eosio.token transfer '[ "testacc", "eosio", "25.0000 CRWD", "m" ]' -p testacc@active

    } 

  private: 
    // Setup the struct that represents the row in the table
    
    /// @abi table listing
    struct listing {
      uint64_t key; // primary key
      std::string title;


      uint32_t target;
      std::string description;
      std::string article;  
      uint64_t offervalue;
      std::string offertoken;  // CRWD, EOS, USD etc        

      std::string company; // company primary key
      time offered; // set when user checks the article
      time expires;
      time closed;

      uint16_t checkcount = 0; // incremented by checks
      uint16_t validatorcount = 0; // incremented by validation

      double primary_key()const { return key; }  
      uint64_t by_offervalue()const { return offervalue; }

    };
    /// @abi table
    typedef eosio::multi_index< N(listing), listing, indexed_by<N(byoffervalue), const_mem_fun<listing, uint64_t, &listing::by_offervalue>>> listings;
    
    /// @abi table check
    struct check {
      uint64_t key; // primary key
      uint64_t listingkey; // fk
      
      uint64_t staked;
      uint64_t earned;  // this is determined and distributed when the contract ends

      std::string company; // company primary key
      std::string checker; // checker primary key
      time checked; // set when user checks the article
      bool vote;

      
      double primary_key()const { return key; }  
      uint64_t by_listingkey()const { return listingkey; }

    };
    /// @abi table
    typedef eosio::multi_index< N(check), check, indexed_by<N(by_listingkey), const_mem_fun<check, uint64_t, &check::by_listingkey>>> checks; 
    

    struct validation {
      uint64_t checkkey; // fk
      uint64_t listingkey; // fk
        uint64_t datetimestamp; 
        std::string validator; // the user who validated 
        time when;
        std::string comment;
        bool vote;  // this is the community vote on whether the check 'fail' was a correct report

        uint64_t primary_key()const { return checkkey;  }  
        uint64_t by_listingkey()const { return listingkey; }
        //** add: by_validatorkey() 
    };
    /// @abi table
    typedef eosio::multi_index< N(validations), validation, indexed_by<N(checkkey), const_mem_fun<validation, uint64_t, &validation::by_listingkey>>> validations;
    
    listings _listings;
    checks _checks;
    validations _validations;  
};

EOSIO_ABI( crowdos, (addlisting)(check)(validate)(payout) )



