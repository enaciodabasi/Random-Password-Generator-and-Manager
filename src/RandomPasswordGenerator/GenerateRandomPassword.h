#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <chrono>


std::array<char, 26> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
std::array<char, 10> numbers = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
std::array<char, 29> symbols = { '.', ',', ':', ';', '!', '?', '*', '/', '-', '_', '|', '#', '+', '%', '&', '(', ')', '=', '[', ']', '{', '}', '~',
'@', '<', '>', '"', '£', '$' };



std::string generateRandomPassword(int passLength) {

	// Generating random numbers
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distrAlph(0, 25);
	std::uniform_int_distribution<> distrNums(0, 9);
	std::uniform_int_distribution<> distrSymb(0, 27);

	// Deciding how many characters, numbers and symbols should be in the password
	std::uniform_int_distribution<> distrPassAlphCount(4, passLength / 2);
	int passAlphCount = distrPassAlphCount(gen);
	int passNumCount = 0;
	int passSymbCount = 0;

	if (passLength == 12) {
		std::uniform_int_distribution<> distrPassNumCount(3, passLength - passAlphCount);
		passNumCount = distrPassNumCount(gen);
		passSymbCount = passLength - (passAlphCount + passNumCount);

	}

	else if (passLength == 16) {
		std::uniform_int_distribution<> distrPassNumCount(4, passLength - passAlphCount);
		passNumCount = distrPassNumCount(gen);
		passSymbCount = passLength - (passAlphCount + passNumCount);
	}

	std::vector<int> indexAlph;
	std::vector<int> indexNums;
	std::vector<int> indexSymb;


	// getting random index numbers for Alphabet, Number and Symbol Arrays

	while (indexAlph.size() != passAlphCount) {
		indexAlph.push_back(distrAlph(gen));
		std::vector<int>::iterator it;
		it = std::unique(indexAlph.begin(), indexAlph.end());
		indexAlph.resize(std::distance(indexAlph.begin(), it));
	}
	while (indexNums.size() != passNumCount) {
		indexNums.push_back(distrNums(gen));
		std::vector<int>::iterator it;
		it = std::unique(indexNums.begin(), indexNums.end());
		indexNums.resize(std::distance(indexNums.begin(), it));
	}
	while (indexSymb.size() != passSymbCount) {
		indexSymb.push_back(distrSymb(gen));
		std::vector<int>::iterator it;
		it = std::unique(indexSymb.begin(), indexSymb.end());
		indexSymb.resize(std::distance(indexSymb.begin(), it));
	}

	// Getting Characters, Numbers and Symbols for the password from their respective arrays

	std::vector<char> passAlph;
	std::vector<char> passNums;
	std::vector<char> passSymb;

	for (int i = 0; i < indexAlph.size(); i++) {

		passAlph.push_back(alphabet[indexAlph[i]]);
	}

	for (int i = 0; i < indexNums.size(); i++) {
		passNums.push_back(numbers[indexNums[i]]);
	}

	for (int i = 0; i < indexSymb.size(); i++) {
		passSymb.push_back(symbols[indexSymb[i]]);
	}

	// Getting the characters, numbers and symbols to create a password
	std::vector<char> passwordMembers;

	for (auto v : passAlph)
		passwordMembers.push_back(v);

	for (auto v : passNums)
		passwordMembers.push_back(v);

	for (auto v : passSymb)
		passwordMembers.push_back(v);

	// Shuffling the password components for randomness;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(passwordMembers.begin(), passwordMembers.end(), std::default_random_engine(seed));

	// Creating the password
	std::string password;

	for (int i = 0; i < passwordMembers.size(); i++)
		password.push_back((passwordMembers.at(i)));



	return password;
}

std::wstring s2ws(const std::string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}		