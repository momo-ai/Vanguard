pragma solidity ^0.8.10;

contract no_msg_value_loop1 {
    mapping(address => uint256) public balances;

    function not_bad(address[] memory receivers, uint256 msg_value) public {
        for (uint256 i=0; i < receivers.length; i++) {
            __for_loop_body_1(receivers, msg_value, i);
        }
    }

    function __for_loop_body_1(address[] memory receivers, uint256 msg_value, uint256 i) internal {
        balances[receivers[i]] += msg_value;
    }

}
