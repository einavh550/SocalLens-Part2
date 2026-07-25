#ifndef EQUIPMENT_H
#define EQUIPMENT_H


class Equipment
{
	int equipmentid;
	char* modelName;
	bool isAvailable;

public:
	Equipment(int id,const char* modelName,bool available = true);
	Equipment(const Equipment& other);
	virtual ~Equipment();

	Equipment& operator=(const Equipment& other);

	int getEquipmentId() const;
	const char* getModelName() const;
	bool getIsAvailable() const;
	void setModelName(const char* name);
	void setIsAvailable(bool available);

	virtual void printSpecs() const =0;

	virtual Equipment* clone() const = 0;

private:

};





#endif

