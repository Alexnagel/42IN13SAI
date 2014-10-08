#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

/*
Also check and parse if-else statement
*/
CompilerNode Parser::ParseIfStatement()
{
	Token currentToken = Compiler::GetNext();
	bool hasPartner = false;

	CompilerNode endNode;

	if (currentToken.Type == TokenType::If)
	{
		if (currentToken.Partner != nullptr)
		{
			hasPartner = true;
		}
	}
	else
	{
		throw std::runtime_error("Expected if keyword");
	}

	Match(TokenType::OpenBracket);

	ParseExpression();

	Match(TokenType::CloseBracket);
	Match(TokenType::OpenCurlyBracket);

	while ((currentToken = GetNext()).Type != TokenType::CloseCurlyBracket)
	{
		//TODO parse stuff in if statement
	}

	if (hasPartner)
	{
		//TODO parse else statement
	}

	return endNode;
}

CompilerNode Parser::ParseExpression()
{
	CompilerNode parsedExpr = ParseRelationalExpression();
}

CompilerNode Parser::ParseRelationalExpression()
{
	CompilerNode parsedExpr = ParseAddExpression();
	return parsedExpr;
}

CompilerNode Parser::ParseAddExpression()
{
	CompilerNode parsedExpr = ParseMulExpression();
	return parsedExpr;
}

CompilerNode Parser::ParseMulExpression()
{
	CompilerNode parsedExpr = ParseUniExpression();
	return parsedExpr;
}

CompilerNode Parser::ParseUniExpression()
{
	CompilerNode term = ParseTerm();
	return term;
}

CompilerNode Parser::ParseTerm()
{
	Token token = GetNext();

	if (token.Type == TokenType::Float)
	{

	}
	else if (token.Type == TokenType::Identifier)
	{
		std::string identifier = token.Value;
		
		/*if (variable == null)
			throw std::exception();*/
	}
	else if (token.Type == TokenType::OpenBracket)
	{
		CompilerNode expr = ParseExpression();
		Match(TokenType::CloseBracket);
		return expr;
	}

	return CompilerNode();
}

/*
Parse while and for loops
*/
CompilerNode Parser::ParseLoopStatement()
{
	Token currentToken = Compiler::GetNext();
	bool forLoop = false;

	CompilerNode endNode;

	if (currentToken.Type != TokenType::While || currentToken.Type != TokenType::ForLoop)
	{
		throw std::runtime_error("Expected a loop keyword");
	}
	else
	{
		if (currentToken.Type == TokenType::ForLoop)
		{
			forLoop = true;
		}
	}

	Match(TokenType::OpenBracket);

	if (forLoop)
	{
		CompilerNode assignmentNode = ParseAssignmentStatement();
		CompilerNode expressionNode = ParseExpression();
		CompilerNode addExpressionNode = ParseAddExpression();
	}
	else
	{
		CompilerNode expressionNode = ParseExpression();
	}

	Match(TokenType::CloseBracket);
	Match(TokenType::OpenCurlyBracket);

	while ((currentToken = GetNext()).Type != TokenType::CloseCurlyBracket)
	{
		//TODO parse stuff in the loop
	}

	return endNode;
}

/*
Also parse (standard) Arithmetical operations
*/
CompilerNode Parser::ParseAssignmentStatement()
{
	std::string expression = "";
	std::vector<std::string> parameters;
	CompilerNode *valueNode = nullptr;
	CompilerNode endNode;

	Token currentToken = GetNext();
	if (currentToken.Type == TokenType::Identifier)
	{
		parameters.push_back(currentToken.Value);
	}
	else
	{
		throw std::runtime_error("Identifier expected");
	}

	currentToken = GetNext();

	if (currentToken.Type == TokenType::Equals)
	{
		expression = "$assignment";
	}

	currentToken = GetNext();

	if (PeekNext()->Type == TokenType::EOL)
	{
		parameters.push_back(currentToken.Value);
		expression = expression;
	}
	else
	{
		CompilerNode node = ParseExpression();
		valueNode = &node;
	}

	if (valueNode != nullptr)
	{
		//TODO make parameters list
		endNode = CompilerNode(expression, &parameters, nullptr);
	}
	else
	{
		endNode = CompilerNode(expression, &parameters, nullptr);
	}

	return endNode;
}
