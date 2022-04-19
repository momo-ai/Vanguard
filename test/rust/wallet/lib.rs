#![cfg_attr(not(feature = "std"), no_std)]


use ink_lang as ink;

#[ink::contract]
mod wallet {
    use ink_storage::{
        traits::SpreadAllocate,
        Mapping,
    };

    use ink_env::call::{
        build_call,
        Call,
        ExecutionInput,
        Selector,
    };

    use ink_env::DefaultEnvironment;

    /// Defines the storage of your contract.
    /// Add new fields to the below struct in order
    /// to add new static storage fields to your contract.
    #[ink(storage)]
    #[derive(SpreadAllocate)]
    pub struct Wallet {
        balances: Mapping<AccountId, Balance>
    }

    impl Wallet {
        #[ink(constructor)]
        pub fn constructor() -> Self {
            ink_lang::utils::initialize_contract(|contract: &mut Self| {})
        }

        #[ink(message, payable)]
        pub fn deposit(&mut self) {
            let updatedBal:Balance = self.balances.get(self.env().caller()).unwrap_or_default() + self.env().transferred_value();
            self.balances.insert(self.env().caller(), &updatedBal);
        }

        #[ink(message)]
        pub fn withdraw(&mut self) {
            let bal:Balance = self.balances.get(self.env().caller()).unwrap_or_default();
            build_call::<DefaultEnvironment>()
                .call_type(Call::new()
                    .callee(self.env().caller())
                    .transferred_value(bal))
                .exec_input(ExecutionInput::new(Selector::new([0xAB, 0xEB, 0xEC, 0xCA])))
                .returns::<()>()
                .fire()
                .unwrap();
            self.balances.insert(self.env().caller(), &0);
        }

        #[ink(message)]
        pub fn getBalance(&self) -> Balance {
            return self.balances.get(self.env().caller()).unwrap_or_default();
        }
    }
}
