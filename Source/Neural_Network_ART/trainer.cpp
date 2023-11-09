#include "trainer.h"

Trainer::Trainer(const std::string filename)
{
	file.open(filename.c_str());
}

bool Trainer::getEOF()
{
	return file.eof();
}

void Trainer::getTopology(std::vector<unsigned>& topology)
{
	std::string line;
	std::string label;

	std::getline(file, line);
	std::stringstream stream(line);
	stream >> label;
	if (this->file.eof() || label.compare("topology:") != 0)
	{
		abort();
	}

	while (!stream.eof())
	{
		unsigned n;
		stream >> n;
		topology.push_back(n);
	}
	return;
}

unsigned int Trainer::getNextInputs(std::vector<double>& inputVals)
{
	inputVals.clear();

	std::string line;
	std::getline(file, line);
	std::stringstream stream(line);

	std::string label;
	stream >> label;
	if (label.compare("in:") == 0) {
		double oneValue;
		while (stream >> oneValue) {
			inputVals.push_back(oneValue);
		}
	}

	return inputVals.size();
}

unsigned int Trainer::getTargetOutputs(std::vector<double>& targetOutputVals)
{
	targetOutputVals.clear();

	std::string line;
	std::getline(file, line);
	std::stringstream stream(line);

	std::string label;
	stream >> label;
	if (label.compare("out:") == 0) {
		double oneValue;
		while (stream >> oneValue) {
			targetOutputVals.push_back(oneValue);
		}
	}

	return targetOutputVals.size();
}