// RUN: python3 vanguard_driver.py --src_path %s --detector statGen
// XFAIL:*
pragma solidity ^0.8.0;

import "./ReentrancyGuard.sol";
import "./Address.sol";
import "./IERC20.sol";

/**
 * @title PuppetPool
 * @author Damn Vulnerable DeFi (https://damnvulnerabledefi.xyz)
 */

contract PuppetPool is ReentrancyGuard {

    using Address for address payable;

    mapping(address => uint256) public deposits;
    address public immutable uniswapPair;
    IERC20 public immutable token;

    constructor (address tokenAddress, address uniswapPairAddress) {
        token = IERC20(tokenAddress);
        uniswapPair = uniswapPairAddress;
    }

    // Allows borrowing `borrowAmount` of tokens by first depositing two times their value in ETH
    function borrow(uint256 borrowAmount) public payable nonReentrant {
        uint256 depositRequired = calculateDepositRequired(borrowAmount);

        require(msg.value >= depositRequired, "Not depositing enough collateral");

        if (msg.value > depositRequired) {
            payable(msg.sender).sendValue(msg.value - depositRequired);
        }

        deposits[msg.sender] = deposits[msg.sender] + depositRequired;

        // Fails if the pool doesn't have enough tokens in liquidity
        bool res = token.transfer(msg.sender, borrowAmount);
        require(res, "Transfer failed");
    }

    function calculateDepositRequired(uint256 amount) public view returns (uint256) {
        return amount * _computeOraclePrice() * 2 / 10 ** 18; 
    }

    function _computeOraclePrice() private view returns (uint256) {
        // calculates the price of the token in wei according to Uniswap pair
        return address(uniswapPair).balance * (10 ** 18) / token.balanceOf(uniswapPair);
    }
}

// CHECK: // each check statement correspondss to a line printed by the detector(?)
//