contract Wallet {
    mapping(address => uint) balances;

    constructor() {
    }

    function deposit() external payable {
        balances[msg.sender] += msg.value;
    }   

    function withdraw1() external {
        uint bal = balances[msg.sender];
        require(bal > 0); 

        payable(msg.sender).transfer(bal);

        clearBalance();
    }   

    function withdraw2() external {
        uint bal = balances[msg.sender];
        require(bal > 0); 

        (bool success, ) = payable(msg.sender).call{value: bal}("");
        require(success, "Address: unable to send value, recipient may have reverted");

        clearBalance();
    }   

    function clearBalance() internal {
        balances[msg.sender] = 0;
    }   

    function getBalance() public view returns (uint) {
        return address(this).balance;
    }   
}
