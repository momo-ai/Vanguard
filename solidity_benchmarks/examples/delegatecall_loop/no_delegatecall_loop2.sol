pragma solidity ^0.8.10;

contract no_delegatecall_loop2 {
    mapping(address => uint256) public balances;
    mapping(address => uint256) public votes;

    function not_bad(address[] memory receivers) public payable {
        for (uint256 i=0; i < receivers.length; i++) {
            __for_loop_body_1(receivers, i);
        }
    }

    function __for_loop_body_1(address[] memory receivers, uint256 i) internal {
        votes[receivers[i]] += 1;
    }
}
