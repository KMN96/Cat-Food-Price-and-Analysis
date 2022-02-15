#define MAX_PRODUCT 3
#define NUM_GRAMS 64
#define KG_TO_LBS 2.20462
// ----------------------------------------------------------------------------
// structures
struct CatFoodInfo
{
	int sku;
	double price;
	int calories;
	double weight;
};

struct ReportData
{
	int sku;
	double rate;
	int calories;
	double weightsLbs;
	double weightsKg;
	int g;
	double totalServe;
	double perServe;
	double calPerServe;
};


// ----------------------------------------------------------------------------
// function prototypes

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

int getIntPositive(int* num);

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

double getDoublePositive(double* num);

// 3. Opening Message (include the number of products that need entering)

void openingMessage(const int numProduct);

// 4. Get user input for the details of cat food product

struct CatFoodInfo getCatFoodInfo(const int numSequence);

// 5. Display the formatted table header

void displayCatFoodHeader();


// 6. Display a formatted record of cat food data

void displayCatFoodData(const int sku, const double price, const int calories, const double weight);




// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg

double convertLbsKg(const double* lb, double* kg);

// 9. convert lbs: g

int convertLbsG(const double* lbs, int* g);

// 10. convert lbs: kg / g

void convertLbs(const double* lbs_convert, double* kg, int* g);

// 11. calculate: servings based on gPerServ

double calculateServings(const int value, const int sum, double* result);

// 12. calculate: cost per serving

double calulateCostPerServing(const double* rate, const double* result, double* costResults);

// 13. calculate: cost per calorie

double calulateCostPerCal(const double* price, const double* calories, double* costCalories);

// 14. Derive a reporting detail record based on the cat food product data

struct ReportData caculateReportData(struct CatFoodInfo getDetailCatFood);

// 15. Display the formatted table header for the analysis results

void displayReportHeader(void);

// 16. Display the formatted data row in the analysis table

void displayReportData(const struct ReportData reportInfo, const int cheap);

// 17. Display the findings (cheapest)

void displayFinalAnaysis(const struct CatFoodInfo cheaperProduct);

// ----------------------------------------------------------------------------

// 7. Logic entry point 

void start();
