// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "./ReentrancyGuard.sol";
import "./Address.sol";
import "IERC20.sol";

/**
 * @title PuppetPool
 * @author Damn Vulnerable DeFi (https://damnvulnerabledefi.xyz)
 */
contract PuppetPool is ReentrancyGuard {

    using Address for address payable;

    mapping(address => uint256) public deposits;
    address public immutable uniswapPair;
    //DamnValuableToken public immutable token;
    IERC20 public immutable token;
    
    event Borrowed(address indexed account, uint256 depositRequired, uint256 borrowAmount);

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
        //require(token.transfer(msg.sender, borrowAmount), "Transfer failed");
        bool res = token.transfer(msg.sender, borrowAmount);
        require(res, "Transfer failed");

        emit Borrowed(msg.sender, depositRequired, borrowAmount);
    }

    function calculateDepositRequired(uint256 amount) public view returns (uint256) {
        return amount * _computeOraclePrice() * 2 / 10 ** 18;
    }

    function v_call_IERC20_balanceOf(IERC20 tok, address addr) internal view returns (uint256) {
        return tok.balanceOf(addr);
    }

    function _computeOraclePrice() private view returns (uint256) {
        // calculates the price of the token in wei according to Uniswap pair
        //return address(uniswapPair).balance * (10 ** 18) / token.balanceOf(uniswapPair);
        return address(uniswapPair).balance * (10 ** 18) / v_call_IERC20_balanceOf(token, uniswapPair);
    }
}

