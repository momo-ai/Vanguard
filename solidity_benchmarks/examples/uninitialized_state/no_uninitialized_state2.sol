pragma solidity ^0.8.10;

contract no_uninitialized_state2 {
    address payable destination;

    function __set_destination(address payable _destination) internal {
        destination = _destination;
    }

    function __get_destination() internal view returns (address payable dst) {
        return destination;
    }

    function transfer() payable public {
        __set_destination(payable(msg.sender));
        __get_destination().transfer(msg.value);
    }


}
