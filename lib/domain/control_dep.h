namespace Domain {
    class control_dependencies {

        public:
            bool resolvesCalls(); 

            std::list<CallEdge> getCallees(context, callinstruction); 

            std::list<CallEdges> getCallers(context, callinstruction); 

        
        // would we also want to declare the CallEdge struct here? For internal use only? Probably not internal only... 

        private: 

            struct CallEdge {

                std::str caller

                std::str callee 
            }
    }
}