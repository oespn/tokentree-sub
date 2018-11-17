#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;


class coschallenge : public eosio::contract {
  public:
    // a challenge begins with a checker raising a challenge
    // this occurs when a company rejects a false vote submission
    // 

    challenge(account_name s):
        contract(s), // initialization of the base class for the contract
        _challenges(s, s), // initialize the table with code and scope NB! Look up definition of code and scope
        _validations(s, s)
    {
    }

    /*
        needs methods for PostChallenge from other smart contract
        push in the list of invited community to verify the submission
        get the challenge description and conditions for the checkers
        checkers review and submit a vote
        on the expiry condition (time or quorum) payout.
    */

    /// @abi action
    void challenge(account_name username, const std::string& title, uint32_t coskey, const std::string& description, uint64_t offervalue, time expires) {
        require_auth(username); // this user is the checker that is challenging
        // Let's make sure the primary key doesn't exist
        eosio_assert(_contracts.find(coskey) == _contracts.end(), "This challenge already exists");
        //** future: charge the sender rather than self 
        
        _challenges.emplace(get_self(), [&]( auto& p ) {
            p.key = _challenges.available_primary_key();
            p.company = username;
            p.title = title,
            p.target = target;
            p.description = description;
            p.offervalue = offervalue;
            p.expires = expires;
            p.votestake = 1;
        });
    } 


  private: 
    // Setup the struct that represents the row in the table
    
    /// @abi table challenge
    struct challenge {
      uint64_t key; // primary key
      uint64_t checkkey; 
      std::string reason;
      std::string description;
      std::string article;  // repo / URL or identifier 

      account_name checker;  
      time offered; // set when user checks the article
      time expires;
      time closed;

      uint16_t checkcount = 0; // incremented by checks
      /*list of checkers invited to earn their stake back*/
      //account_name checker; 
      uint64_t primary_key()const { return key; }  
      account_name get_company() const {return company; }
      time by_expires()const { return expires; }

    };
    /// @abi table
    typedef eosio::multi_index<
      N(challenge), challenge, 
      indexed_by<
        N(byoffervalue), 
        const_mem_fun<challenge, uint64_t, &challenge::by_expires>
        >
    > challenges;
};

EOSIO_ABI( coschallenge, (postchallenge)(validate)(payout) )
