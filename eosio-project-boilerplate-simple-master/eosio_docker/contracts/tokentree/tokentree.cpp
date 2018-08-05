#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

//#include "tokentree.hpp"

using namespace eosio;

//namespace tokentree {

class treestory : public eosio::contract {
  public:
    // a treestory begins with a sponsor
    // the sponsor sets the location, description and the offervalue (in TRE), radius in meters
    // contract has a life or maximum quota of trees?

    //** expansion: the treestory would originate from a greater sponsorship offer 
    // the sponsorship offer contains: 
    // - organiser
    // - logistics
    // - prefererred tree type
    // - conditions and warnings 

    // once created a planter can take on the offer for it's value
    // a % of the offer is set aside for validators
    // the validatons record a vote & comment

    // payout checks that at least min_validation count validations have been done 

    // What next?
    // Implement database as mongodb. Store hashes of records to the blockchain
    // Implement true latitude,longitude and use db functions for indexing and locating in geo

    treestory(account_name s):
        contract(s), // initialization of the base class for the contract
        _treepatchs(s, s), // initialize the table with code and scope NB! Look up definition of code and scope
        _trees(s,s),
        _validations(s, s)
    {
    }

    // geo_double idx_long_double 
    struct geo_location {
        double latitude;
        double longitude;
        //later: expand to support a region list or lat,lng vectors 
    };

    /// @abi action
    void addoffer(account_name username, double geo, uint32_t radius, const std::string& description, uint64_t offervalue, time expires) {
        require_auth(username); // this user is a sponsor
        // Let's make sure the primary key doesn't exist
        eosio_assert(_treepatchs.find(geo) == _treepatchs.end(), "This lat,lng already exists in the tree patches");
        //** future: charge the sender rather than self 
        
        _treepatchs.emplace(get_self(), [&]( auto& p ) {
            p.sponsor = username;
            p.geo = geo;         
            //p.geo_location.latitude = getSignificant(geo);
            //p.geo_location.longitude = getDecimals(geo);
            p.radius = radius;
            p.description = description;
            p.offervalue = offervalue;
            p.expires = expires;
        });
    } 

    /// @abi action
    void plant(account_name username, double geo, double treepatchkey, time planted) {
        // usage: assume caller is the Planter
        require_auth(username); // this user is a planter
        // Let's make sure the primary key doesn't exist
        eosio_assert(_trees.find(treepatchkey) == _trees.end(), "This lat,lng of tree already exists in the treestory treelist");
        
        //get from treepatchkey
        auto treepatch = _treepatchs.find(treepatchkey);
        //** future: assert geo is inside radius
        //eosio_assert(inside_radius(geo, treepatch->radius); 

        time now = current_time();
        eosio_assert(treepatch->expires > now, "You cannot plant for an expired offer");

        _trees.emplace(get_self(), [&]( auto& p ) {
            p.planter = username;
            p.sponsor = treepatch->sponsor;
            p.geo = geo;         
            //p.geo_location.latitude = extractLat(geo);
            //p.geo_location.longitude = extractLng(geo);
            p.planted = planted;
        });

        if (treepatch != _treepatchs.end())
        {
            _treepatchs.modify(treepatch, get_self(), [&](auto& p)
                                        {
                                            p.treecount = p.treecount + 1;
                                        });
        }
    } 

    /// @abi action
    void validate(account_name username, double treepatchkey, time validated, std::string comment, uint8_t health) {
        require_auth(username); // this user is a validator
        // Let's make sure the primary key doesn't exist
        // key = treeId, datetime, user
        auto tree = _trees.find(treepatchkey);
        auto treepatch = _treepatchs.find(tree->geo);
        eosio_assert(tree != _trees.end(), "The lat,lng of tree already exists in the treestory treelist");
        // assert offer hasn't expired 
        time now = current_time();
        eosio_assert(treepatch->expires > now, "You cannot validate a tree for an expired offer");

        _validations.emplace(get_self(), [&]( auto& p ) {
            //p.geo = geo;     
            p.treegeokey = treepatchkey;
            p.validator = username; // the user who validated primary key
            p.when = validated;
            p.datetimestamp = validated; // as epoch
            p.comment = comment;
            p.health = health;
        });

        if (treepatch != _treepatchs.end())
        {
            _treepatchs.modify(treepatch, get_self(), [&](auto& p)
                                        {
                                            p.validatecount = p.validatecount + 1;
                                        });
        }
    } 


    /// @abi action
    void payout(account_name username, double treepatchkey, time closed) {
        require_auth(username); // this user is a validator


        // Let's make sure the primary key doesn't exist
        // key = treeId, datetime, user
        //auto tree = _trees.find(geo);
        
        auto treepatch = _treepatchs.find(treepatchkey);
        if (treepatch != _treepatchs.end())
        {
            _treepatchs.modify(treepatch, get_self(), [&](auto& p)
                                        {
                                            p.closed = closed;
                                        });
        }

        auto plantertokens = treepatch->offervalue/2;
        // half of tokens go to the tree planters 
        //** future: check that they have at least 3 verifications by other parties
        auto planterpay = plantertokens / treepatch.validatecount;
        std::vector<double> treesForModify;
          // find all tree items
          for(auto& item : _trees)
          {
              if (item.geo == treepatchkey)
              {
                  treesForModify.push_back(item.geo);   
              }
          }
          // update the paid out tokens to each planter
          for (double key : treesForModify)
          {
              //seek the planter & payout
          }

        // balance divided by the tree verifiers 
        auto verifiertokens = treepatch->offervalue - planterpay; 
        auto verifierpay = verifiertokens / treepatch.validatecount;
        
          // find all tree verifiers
          std::vector<double> keysForModify;
          for(auto& item : _validations)
          {
              if (item.treegeokey == treepatchkey)
              {
                  keysForModify.push_back(item.treegeokey);   
              }
          }
          // update the paid out tokens to each planter
          for (double key : keysForModify)
          {
              //seek the validator & payout
          }

        // for each associated validation - pay out the share of the tokens
        
        //** action eosio.token transfer '[ "testacc", "eosio", "25.0000 TRE", "m" ]' -p testacc@active

    } 

  private: 
    // Setup the struct that represents the row in the table


    
    /// @abi table treepatch
    struct treepatch {
      double geo; // primary key, geo location
        //geo_location.latitude = extractLat(geo);
        //geo_location.longitude = extractLng(geo);
      uint32_t radius;
      std::string description;
      uint64_t offervalue;

      std::string sponsor; // sponsor primary key
      time offered; // set when user plants the tree
      time expires;
      time closed;

      uint16_t treecount = 0; // incremented by trees
      uint16_t validatorcount = 0; // incremented by validation

      double primary_key()const { return geo; }  
      // PK is DMS Degree, Minutes, Seconds format to agree with a single long double 
      // See: https://stackoverflow.com/questions/1140189/converting-latitude-and-longitude-to-decimal-values
      uint64_t by_offervalue()const { return offervalue; }

    };
    /// @abi table
    typedef eosio::multi_index< N(treepatch), treepatch, indexed_by<N(byoffervalue), const_mem_fun<treepatch, uint64_t, &treepatch::by_offervalue>>> treepatchs;
    //** future: mongodb provide the efficent geo lookup index  
    
    /// @abi table tree
    struct tree {
      double geo; // primary key, geo location
      //geo_location store 
      double latitude;
      double longitude; 
      uint64_t earned;  // this is determined and distributed when the contract ends

      std::string sponsor; // sponsor primary key
      std::string planter; // planter primary key
      time planted; // set when user plants the tree

      uint8_t approxheight; // indication of tree maturity

      double primary_key()const { return geo; }  
      uint64_t by_approxheightvalue()const { return approxheight; }

    };
    /// @abi table
    typedef eosio::multi_index< N(tree), tree, indexed_by<N(by_approxheightvalue), const_mem_fun<tree, uint64_t, &tree::by_approxheightvalue>>> trees;
    //** expansion: mongodb provide the efficent geo lookup index  
    

    struct validation {
        double treegeokey; //PK
        uint64_t datetimestamp; //PK
        std::string validator; // the user who validated primary key
        time when;
        std::string comment;
        uint8_t health = 100;  // default to 100%

        // hash of tree PK + verification
        double primary_key()const { return treegeokey+datetimestamp;  }  
        uint64_t by_treepatchgeokey()const { return treegeokey; }
    };
    /// @abi table
    typedef eosio::multi_index< N(validations), validation, indexed_by<N(treegeokey), const_mem_fun<validation, uint64_t, &validation::by_treepatchgeokey>>> validations;
    
    treepatchs _treepatchs;
    trees _trees;
    validations _validations;  


};

EOSIO_ABI( treestory, (addoffer)(plant)(validate)(payout) )
//(payout) 


