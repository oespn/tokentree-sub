// ************** NOT FOR COMPILATION ***************
// Extracted from the Smart Contract
// with intention of determining what tables need to be added 

#include <eosiolib/eosio.hpp>

using namespace eosio;

// NEW tables to be added:
// For Firebase DB?

class newTables {
  public:

    // user completes profile (or signs up with social and adds identity)
    struct userprofile {
      account_name userkey; // FK mapping to EOS user account
      std::string email;
      std::string first_name;
      std::string last_name; 
      std::string avatar;

      uint32_t votes_total; 
      uint32_t votes_correct; // for user rating

      uint32_t bounties_awarded; 
      uint32_t challenges_raised; 
      uint32_t challenges_won;

      uint32_t tokens_earned;
    }

    struct companyprofile {
      account_name userkey; // FK mapping to EOS user account
      std::string email;
      std::string company_name; 
      std::string first_name;
      std::string last_name; 
      std::string logo;

      uint32_t listings_total; 
      uint32_t bounties_awarded; 
    }




}



// FROM CrowdOS Smart Contract

class crowdos {
  public:

    struct listing {
      uint64_t key; // primary key
      std::string title;
      uint32_t target;

      uint8_t type;

      std::string description;
      std::string article;  // repo / URL or identifier 


      uint16_t votestake;  // how much CRWD to 'bet' when voting
      uint64_t offervalue;
      //std::string offertoken;  // CRWD, EOS, USD etc   assume CRWD for MVP       

      account_name company; // company primary key
      time offered; // set when user checks the article
      time expires;
      time closed;

      uint16_t checkcount = 0; // incremented by checks
      uint16_t validatorcount = 0; // incremented by validation

      uint64_t primary_key()const { return key; }  
      account_name get_company() const {return company; }
      uint64_t by_offervalue()const { return offervalue; }

    };


    struct check {
      uint64_t key; // primary key
      uint64_t listingkey; // fk
      account_name checker; // fk
      
      uint64_t staked;
      uint64_t earned;  // this is determined and distributed when the contract ends

      time checked; // set when user checks the article
      bool vote;
      std::string comment;

      uint64_t primary_key()const { return key; }  
      account_name get_checker() const {return checker; }
      uint64_t by_listingkey()const { return listingkey; }

    };


struct validation {
      uint64_t checkkey; // fk
      uint64_t listingkey; // fk
        uint64_t datetimestamp; 
        account_name validator; // the user who validated 
        time when;
        std::string comment;
        bool vote;  // this is the community vote on whether the check 'fail' was a correct report

        uint64_t primary_key()const { return checkkey;  }  
        uint64_t by_listingkey()const { return listingkey; }
        account_name by_validatorkey()const { return validator; }
    };

}