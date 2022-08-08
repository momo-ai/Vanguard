namespace Domain {
    class data_dependencies {
        public:

            bool hasAdditionalStorage();

            // is valueish an int? 

            std::list<> getAdditionalStorage();

            bool readsStorage(instruction); 

            bool writesStorage(instruction);

            std::list<> getStorageReads(instruction); 

            std::list<> getStorageWrites(instruction); 

    }
}