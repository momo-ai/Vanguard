pragma solidity ^0.8.10;

contract no_delegatecall_loop1 {
    mapping(address => uint256) public balances;
    mapping(address => uint256) public votes;

    function not_bad(address[] memory receivers) public {
        for (uint256 i=0; i < receivers.length; i++) {
            __for_loop_body_1(receivers, i);
        }
    }

    function __for_loop_body_1(address[] memory receivers, uint256 i) internal {
        (bool check, ) = address(this).delegatecall(abi.encodeWithSignature("addVote(address)", receivers[i]));
    }

    function addVote(address a) public {
        votes[a] += 1;
    }
}
