#include "DataCollector.h"

DataCollector::DataCollector(const std::string& docPath):
	doc()
{
	doc.Load(docPath);
}

