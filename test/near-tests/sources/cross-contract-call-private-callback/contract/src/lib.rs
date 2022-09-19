use near_sdk::borsh::{self, BorshDeserialize, BorshSerialize};
use near_sdk::{env, log, near_bindgen, AccountId, Gas, Promise, PromiseError, PanicOnDefault};

pub mod external;
pub use crate::external::*;

#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize, PanicOnDefault)]
pub struct Contract {
  pub hello_account: AccountId
}

#[near_bindgen]
impl Contract {
  #[init]
  #[private] // Public - but only callable by env::current_account_id()
  pub fn new(hello_account: AccountId) -> Self {
    assert!(!env::state_exists(), "Already initialized");
    Self {
      hello_account,
    }
  }

  // Public - query external greeting
  pub fn query_greeting(&self) -> Promise {
    // Create a promise to call HelloNEAR.get_greeting()
    let promise = hello_near::ext(self.hello_account.clone())
      .with_static_gas(Gas(5*TGAS))
      .get_greeting();
    
    return promise.then( // Create a promise to callback query_greeting_callback
      Self::ext(env::current_account_id())
      .with_static_gas(Gas(5*TGAS))
      .query_greeting_callback()
    )
  }

  #[private] // Public - but only callable by env::current_account_id()
  pub fn query_greeting_callback(&self, #[callback_result] call_result: Result<String, PromiseError>) -> String {
    // Check if the promise succeeded by calling the method outlined in external.rs
    if call_result.is_err() {
      log!("There was an error contacting Hello NEAR");
      return "".to_string();
    }

    // Return the greeting
    let greeting: String = call_result.unwrap();
    greeting
  }
}
