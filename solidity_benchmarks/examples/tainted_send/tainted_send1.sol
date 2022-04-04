pragma solidity ^0.8.10;

contract tainted_send1 {
    address payable destination;

    function setDestination() public {
        destination = payable(msg.sender);
    }

    function withdraw() public {
        destination.transfer(address(this).balance);
    }
}
