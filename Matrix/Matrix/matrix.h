#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
namespace My {
	
	template<typename T>
	class Matrix
	{
	private:
		std::vector<std::vector<T>> body_;

		class Part
		{
		private:
			std::vector<T> pbody_;
		public:
			Part(std::vector<T>& v) :pbody_(v) {};
			T& operator[](int index) { return pbody_[index]; };
		};

		Matrix getWithoutRowandColumn(int i1, int j1) {
			Matrix ans;

			for (int i = 0; i < body_.size(); i++) {
				if (i != i1) {
					std::vector<T> p;
					for (int j = 0; j < body_[0].size(); j++) {
						if (j != j1)
						{
							p.push_back(body_[i][j]);
						}
					}
					ans.body_.push_back(p);
				}
			}

			return ans;
		};
	public:
		Matrix() = default;
		void input() { std::cin >> *this; };
		void input(const std::string& fileName) { std::ifstream F(fileName); F >> *this; F.close(); };
		void output() { std::cout << *this; };
		void output(const std::string& fileName) { std::ofstream F(fileName); F << *this; F.close(); };
		void generate(int n, int m)
		{
			body_ = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));

			srand(time(0));

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					body_[i][j] = rand() % (n * m * 10);
				}
			}
		};

		Matrix operator+(const Matrix& M)
		{	
			if (M.body_.size() == body_.size() && M.body_[0].size() == body_[0].size())
			{
				Matrix ans = *this;

				for (int i = 0; i < body_.size(); i++) {
					for (int j = 0; j < body_[0].size(); j++) {
						ans.body_[i][j] += M.body_[i][j];
					}
				};

				return ans;

			}
			return *this;
		};
		Matrix operator-(const Matrix& M)
		{
			if (M.body_.size() == body_.size() && M.body_[0].size() == body_[0].size())
			{
				Matrix ans = *this;

				for (int i = 0; i < body_.size(); i++) {
					for (int j = 0; j < body_[0].size(); j++) {
						ans.body_[i][j] -= M.body_[i][j];
					}
				};

				return ans;

			}
			return *this;
		};
		Matrix operator*(const Matrix& M)
		{
			if (body_[0].size() == M.body_.size()) {

				Matrix ans;

				ans.body_ = std::vector<std::vector<T>>(body_.size(), std::vector<T>(M.body_[0].size(), 0));

				for (int i = 0; i < body_.size(); i++) {
					for (int j = 0; j < body_[0].size(); j++) {
						for (int k = 0; k < M.body_[0].size(); k++) {
							ans.body_[i][k] += this->body_[i][j] * M.body_[j][k];
						}
					}
				}
				return ans;

			}

			return *this;
		}

		Part operator[](int index) { return Part(body_[index]); };

		T determinant()
		{
			if (body_.size() != body_[0].size())
				return 0;
			int det = 0;
			int degree = 1; 

			if (body_.size() == 1) 
			{
				return body_[0][0];
			}
			else 
				if (body_.size() == 2)
				{
					return body_[0][0] * body_[1][1] - body_[0][1] * body_[1][0];
				}
				else
				{
					for (int j = 0; j < body_.size(); j++) {
						Matrix newMatrix = getWithoutRowandColumn(0, j);

						det += degree * body_[0][j] * newMatrix.determinant();
						//"Накручиваем" степень множителя
						degree *= -1;
					}
				}

			return det;

		};

		template<typename T> friend std::ostream& operator << (std::ostream& out, Matrix<T>& arg);
		template<typename T> friend std::istream& operator >> (std::istream& inpt, Matrix<T>& arg);
	};



	template<typename T>
	std::ostream& operator<<(std::ostream& out, Matrix<T>& arg)
	{
		out << arg.body_.size() << " " << arg.body_[0].size() << std::endl;

		for (const auto& i : arg.body_)
		{
			for (const auto& j : i)
			{
				out << j << " ";
			}
			out << std::endl;
		}
		return out;
	}

	template<typename T>
	std::istream& operator>>(std::istream& inpt, Matrix<T>& arg)
	{
		int n, m;
		inpt >> n >> m;

		arg.body_ = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));

		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < m; j++) 
			{
				inpt >> arg.body_[i][j];
			}
		}
		return inpt;
	}

}
#endif