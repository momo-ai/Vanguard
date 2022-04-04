pragma solidity ^0.8.10;

contract uninitialized_state1 {
    address payable destination;

    function __set_destination(address payable _destination) internal {
        destination = _destination;
    }

    function __get_destination() internal view returns (address payable dst) {
        return destination;
    }

    function transfer() payable public {
        __get_destination().transfer(msg.value);
    }


}
