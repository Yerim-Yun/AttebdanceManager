#pragma once
#include <string>

using namespace std;

class IGrade {
public:
	virtual ~IGrade() = default;
	virtual string getGradeName() const = 0;
	virtual bool isMeetCriteria(int points) const = 0;
};

class NormalGrade : public IGrade {
public:
	string getGradeName() const override;
	bool isMeetCriteria(int points) const override;
};

class SilverGrade : public IGrade {
public:
	string getGradeName() const override;
	bool isMeetCriteria(int points) const override;
};

class GoldGrade : public IGrade {
public:
	string getGradeName() const override;
	bool isMeetCriteria(int points) const override;
};