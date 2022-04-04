contract Token {
    mapping(address => uint256) balances;
    function transferFrom(address _from, address _to, uint256 _value) public returns (bool success) {
        if (_value > balances[_from]) return false;
        balances[_from] = balances[_from] - _value;
        balances[_to] = balances[_to] + _value;
        return true;
    }
}
contract unchecked_transfer1 {
    mapping(address => uint) balances;
    Token token;
    function deposit(uint amount) public{
        extern_transferFrom(token, msg.sender, address(this), amount);
        balances[msg.sender] += amount;
    }

    function extern_transferFrom(Token _token, address _from, address _to, uint256 _value) internal returns (bool foo) {
        return _token.transferFrom(_from, _to, _value);
    }
}
