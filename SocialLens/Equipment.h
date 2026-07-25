#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <memory>


class Equipment
{
	int equipmentid;
	std::string modelName;
	bool isAvailable;

public:
	Equipment(int id,const char* modelName,bool available = true);
	Equipment(const Equipment& other) = default;
	virtual ~Equipment() = default;

	Equipment& operator=(const Equipment& other) = default;

	int getEquipmentId() const;
	const char* getModelName() const;
	bool getIsAvailable() const;
	void setModelName(const char* name);
	void setIsAvailable(bool available);

	virtual void printSpecs() const =0;

	virtual std::unique_ptr<Equipment> clone() const = 0;

private:

};





#endif

