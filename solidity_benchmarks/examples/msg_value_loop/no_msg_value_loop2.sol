pragma solidity ^0.8.10;

contract no_msg_value_loop2 {
    mapping(address => uint256) public balances;

    function not_bad(address[] memory receivers) public payable {
        uint256 value = msg.value;
        for (uint256 i=0; i < receivers.length; i++) {
            __for_loop_body_1(receivers, value, i);
        }
    }

    function __for_loop_body_1(address[] memory receivers, uint256 value, uint256 i) internal {
        balances[receivers[i]] += value/receivers.length;
    }
}
