//global consts identical to the whole pipeline
#ifndef GLOBALCONSTS_H
#define GLOBALCONSTS_H

const int RouteTypeAmount = 1;
const int MaxOrder = 8;
const int J1 = 1;

const std::string TypeStr[RouteTypeAmount] = { "0" };// , "1", "2" };
const int minSubOrder[RouteTypeAmount] = { 1 };//, 3, 1 };


//Section: paths and so on
//delimeter
const std::string Delimiter = "\\";
const std::string MathDelimiter = "\\\\";


//directories for result files from different stages
const std::string ProjectFolder="..\\..";
const std::string ResultsFolder = ProjectFolder+ Delimiter +"Results"+ Delimiter;
const std::string InputDataFolder = ProjectFolder + Delimiter + "InputData" + Delimiter;


//full paths
//initial input data dirs
const std::string ConfigFilePath = InputDataFolder + "config.txt";
const std::string DirForMatrixInput = InputDataFolder + "matrixes" + Delimiter;
const std::string MatrixVersionPrefix = "b3_";
const std::string DirForPerturbationSeries = InputDataFolder + "perturbationTerms" + Delimiter;
//paths for results dirs
const std::string DirForResultsFromStage0 = ResultsFolder + "Stage0" + Delimiter;
const std::string DirForResultsFromStage1  = ResultsFolder + "Stage1" + Delimiter;
const std::string DirForResultsFromStage11 = ResultsFolder + "Stage1.1" + Delimiter;
const std::string DirForResultsFromStage2 = ResultsFolder + "Stage2" + Delimiter;
const std::string DirForResultsFromStage3 = ResultsFolder + "Stage3" + Delimiter;
const std::string DirForSystemsOnStage3 = "Systems";
const std::string DirForSolutionsOnStage3 = "Solutions";
const std::string DirForResultsFromStage35 = ResultsFolder + "Stage3.5" + Delimiter;
const std::string DirForResultsFromStage4 = ResultsFolder + "Stage4" + Delimiter;
const std::string DirForResultsFromStage5 = ResultsFolder + "Stage5" + Delimiter;

#endif // !GLOBALCONSTS_H