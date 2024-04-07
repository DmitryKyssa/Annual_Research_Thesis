#pragma once

#include <vector>
#include <string>
#include "neuron.h"

static std::vector<std::string> networksNames = {
		"Emma", "Olivia", "Ava", "Isabella", "Sophia",
		"Mia", "Charlotte", "Amelia", "Harper", "Evelyn",
		"Abigail", "Emily", "Elizabeth", "Sofia", "Avery",
		"Ella", "Scarlett", "Grace", "Chloe", "Victoria",
		"Riley", "Aria", "Lily", "Aubrey", "Zoey",
		"Penelope", "Lillian", "Addison", "Layla", "Natalie",
		"Camila", "Hannah", "Brooklyn", "Zoe", "Nora",
		"Leah", "Savannah", "Audrey", "Claire", "Eleanor",
		"Skylar", "Ellie", "Stella", "Paisley", "Maya",
		"Hailey", "Aaliyah", "Kinsley", "Madelyn", "Ariana",
		"Cora", "Alaina", "Violet", "Kylie", "Melanie",
		"Bailey", "Caroline", "Valentina", "Ruby", "Jade",
		"Isabel", "Alice", "Ximena", "Aurora", "Nova",
		"Emery", "Emilia", "Autumn", "Quinn", "Nevaeh",
		"Josephine", "Sarah", "Cora", "Sadie", "Piper",
		"Lydia", "Alexa", "Taylor", "Katherine", "Eliana",
		"Vivian", "Willow", "Reagan", "Brianna", "Clara",
		"Faith", "Ashley", "Emerson", "Sophie", "Annabelle"
};

class Net
{
private:
	std::vector<Layer> layers;
	double error;
	double previousAverageError;
	const double smooth = 100.0;
	std::string name;
	int fitness;
public:
	Net(const std::vector<unsigned int>& topology, std::string& name);
	Net(const Net& original);
	void forwardPropagation(const std::vector<double>& inputVals);
	void backPropagation(const std::vector<double>& targetVals);
	std::vector<double> getResults() const;
	double getRecentAverageError() const;
	double getError() const;
	std::vector<Layer> getLayers() const;
	std::string getName() const;
	int getFitness() const;
	void setName(std::string& newName);
	void setFitness(int fitness);
	Net& operator=(const Net& other);
};