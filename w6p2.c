
#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include <stdio.h>

// User-Defined Libraries

#include "w6p2.h"

// ----------------------------------------------------------------------------
// PART-1

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

int getIntPositive(int* num) {
	int value;
	do
	{
		scanf("%d", &value);
		if (value <= 0)
		{
			printf("ERROR: Enter a positive value: ");
		}
	} while (value <= 0);
	if (num != NULL)
		*num = value;
	return value;
}

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

double getDoublePositive(double* num) {
	double value;
	do
	{
		scanf("%lf", &value);
		if (value <= 0)
		{
			printf("ERROR: Enter a positive value: ");
		}

	} while (value <= 0);
	if (num != NULL)
		*num = value;
	return value;

}

// 3. Opening Message (include the number of products that need entering)

void openingMessage(const int numProduct) {
	printf("Cat Food Cost Analysis\n");
	printf("======================\n\n");
	printf("Enter the details for %d dry food bags of product data for analysis.\n", numProduct);
	printf("NOTE: A 'serving' is %dg\n", NUM_GRAMS);
}


// 4. Get user input for the details of cat food product

struct CatFoodInfo getCatFoodInfo(const int numSequence) {
	struct CatFoodInfo foodInfo = { 0 };
	printf("\nCat Food Product #%d\n", numSequence + 1);
	printf("--------------------\n");
	printf("SKU           : ");
	getIntPositive(&foodInfo.sku);
	printf("PRICE         : $");
	getDoublePositive(&foodInfo.price);
	printf("WEIGHT (LBS)  : ");
	getDoublePositive(&foodInfo.weight);
	printf("CALORIES/SERV.: ");
	getIntPositive(&foodInfo.calories);

	return foodInfo;
}


// 5. Display the formatted table header
void displayCatFoodHeader(void)
{
	printf("\n");
	printf("SKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}

// 6. Display a formatted record of cat food data

void displayCatFoodData(const int sku, const double price, const int calories, const double weight) {
	printf("%07d %10.2lf %10.1lf %8d\n", sku, price, weight, calories);
}

// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg (divide by 2.20462)

double convertLbsKg(const double* lbs, double* kg) {
	double i;
	i = *lbs / KG_TO_LBS;
	if (kg != NULL)
	{
		*kg = i;
	}
	return(i);
}


// 9. convert lbs: g (call convertKG, then * 1000)

int convertLbsG(const double* lbs, int* g) {
	int j;
	j = convertLbsKg(lbs, 0) * 1000;
	if (g != NULL)
	{
		*g = j;
	}
	return(j);
}

// 10. convert lbs: kg and g

void convertLbs(const double* lbsCovert, double* kg, int* g) {
	convertLbsKg(lbsCovert, kg);
	convertLbsG(lbsCovert, g);
}


// 11. calculate: servings based on gPerServ

double calculateServings(const int volume, const int sum, double* result) {
	double i;
	i = (double)sum / (double)volume;
	if (result != NULL)
	{
		*result = i;
	}
	return(i);
}

// 12. calculate: cost per serving

double calculateCostPerServing(const double* rate, const double* result, double* costResult) {
	double cost = 0;
	cost = *rate / *result;
	if (costResult != NULL)
	{
		*costResult = cost;
	}
	return(cost);
}

// 13. calculate: cost per calorie

double calculateCostPerCal(const double* price, const double* calories, double* costCalories) {
	double cost = 0;
	cost = *price / *calories;
	if (costCalories != NULL)
	{
		*costCalories = cost;
	}
	return(cost);
}


// 14. Derive a reporting detail record based on the cat food product data

struct ReportData calculateReportData(const struct CatFoodInfo getDetailCatFood)
{
	struct ReportData reportInfo;
	double cal;

	reportInfo.sku = getDetailCatFood.sku;
	reportInfo.rate = getDetailCatFood.price;
	reportInfo.weightsLbs = getDetailCatFood.weight;
	reportInfo.calories = getDetailCatFood.calories;
	reportInfo.weightsKg = convertLbsKg(&getDetailCatFood.weight, &reportInfo.weightsKg);
	reportInfo.g = convertLbsG(&getDetailCatFood.weight, &reportInfo.g);
	reportInfo.totalServe = calculateServings(NUM_GRAMS, reportInfo.g, &reportInfo.totalServe);
	cal = reportInfo.calories * reportInfo.totalServe;
	reportInfo.perServe = calculateCostPerServing(&reportInfo.rate, &reportInfo.totalServe, &reportInfo.perServe);
	reportInfo.calPerServe = calculateCostPerCal(&reportInfo.rate, &cal, &reportInfo.calPerServe);

	return(reportInfo);
};


// 15. Display the formatted table header for the analysis results
void displayReportHeader(void)
{
	printf("\n");
	printf("Analysis Report (Note: Serving = %dg\n", NUM_GRAMS);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}

// 16. Display the formatted data row in the analysis table

void displayReportData(const struct ReportData reportInfo, const int cheap) {
	printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf", reportInfo.sku, reportInfo.rate, reportInfo.weightsLbs, reportInfo.weightsKg,
		reportInfo.g, reportInfo.calories, reportInfo.totalServe, reportInfo.perServe, reportInfo.calPerServe);
}

// 17. Display the findings (cheapest)

void displayFinalAnalysis(const struct CatFoodInfo cheaper_product) {
	printf("\n");
	printf("Final Analysis\n");
	printf("--------------\n");
	printf("Based on the comparison data, the PURRR-fect economical option is:\n");
	printf("SKU:%07d Price: $%.2lf\n\n", cheaper_product.sku, cheaper_product.price);
	printf("Happy shopping!");
}

// ----------------------------------------------------------------------------

// 7. Logic entry point
void start(void)
{
	struct CatFoodInfo catFoodDetail[MAX_PRODUCT];
	{
		int i = 0, cheapProduct = 0;
		openingMessage(MAX_PRODUCT);
		for (i = 0; i < MAX_PRODUCT; i++)
		{
			catFoodDetail[i] = getCatFoodInfo(i);
		}

		displayCatFoodHeader();
		for ( i = 0; i < MAX_PRODUCT; i++)
		{
			displayCatFoodData(catFoodDetail[i].sku, catFoodDetail[i].price, catFoodDetail[i].calories, catFoodDetail[i].weight);
		}

		struct ReportData reportArray[MAX_PRODUCT];
		displayReportHeader();
		for (i = 0; i < MAX_PRODUCT; i++)
		{
			reportArray[i] = calculateReportData(catFoodDetail[i]);
			if (reportArray[i].perServe < reportArray[i - 1].perServe)
			{
				cheapProduct = i;
			}
		}
		int j;
		for (j = 0; j < MAX_PRODUCT; j++)
		{
			struct ReportData x = { 0 };
			x = reportArray[j];
			displayReportData(x, cheapProduct);
			if (cheapProduct == j)
			{
				printf(" ***");
			}
			printf("\n");
			
		}
		displayFinalAnalysis(catFoodDetail[cheapProduct]);
	};
}
