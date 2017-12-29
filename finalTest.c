#include <stdio.h>
#include <string.h>
#define MAX_PRODUCT 10
#define MAX_TRANS 10


void clr_buff(void){
	int c;
	do {
		c = getchar();
	} while(c != '\n' && c != EOF);
}

typedef struct {
	int productID;
	char productName[30]; 
	int quantity;
	float price;
} Product;

typedef struct {
	int productID;
	int quantity;
	float total;
} TransDetail;



int main()
{
	//INPUT DECLARATION*************************
	int choice, product_num, i;
	char ch;
	int ch_num;
	char searchProductName[30];
	product_num = 0;
	Product productList[MAX_PRODUCT];
	TransDetail transList[MAX_TRANS];

	int s_count;
	int s_productID;
	int s_quantity;
	double s_total;
	//******************************************

	do
	{
		printf("\n\n************************\n MENU_BASED APPLICATION: \n\n");
		printf("1. Input Product\n");
		printf("2. Add Product\n");
		printf("3. Check Store\n");
		printf("4. Search Product\n");
		printf("5. Sell product\n");
		printf("6. Exit Application\n\n");
		printf("Enter a number (1-3):");

		choice=getchar();

		switch(choice)
		{
			case '1':
				{
					printf("How many product(s) you want to input? :");
						scanf("%d", &product_num);
					while(product_num <= 0 || product_num > MAX_PRODUCT){
						printf("There are errors, Please input product number from 1->10.\n");
						printf("How many product(s) you want to input, again? :");
						scanf("%d", &product_num);
					}
					for (i = 0 ; i < product_num ; i++){
						clr_buff();
						//ID
						productList[i].productID =  i ;
						//Name
						printf("Enter product %d name: " , i+1);
						gets(productList[i].productName);

						//Quantity
						printf("Enter product %d quantity: " , i+1);
						scanf("%d", &productList[i].quantity);
							
						while(productList[i].quantity < 0){
							printf("Oops, the quantity must be larger or equal to zero.\n");
							printf("Please reenter product %d quantity:" , i+1);
							scanf("%d", &productList[i].quantity);
						}

						//Price
						printf("Enter product %d price($):" , i+1);
						scanf("%f", &productList[i].price);

						while(productList[i].price <= 0){
							printf("Oops, the price must be larger than zero.\n");
							printf("Reenter product %d price($):" , i+1);
							scanf("%f", &productList[i].price);
						}
						printf("...\n");
					}

					printf("DONE!\n");
					clr_buff();
				} break;
				
			case '2':
				{
					ch = 'Y';
					while(ch == 'Y'){
							clr_buff();
							//Get the next slot i to put new product 
							i = product_num;
							product_num ++;

							//ID
							productList[i].productID =  i;

							//Name
							printf("Enter product %d name: " , i+1);
							gets(productList[i].productName);
							

							//Quantity
							printf("Enter product %d quantity: " , i+1);
							scanf("%d", &productList[i].quantity);
								
							while(productList[i].quantity < 0){
								printf("Oops, the quantity must be >= 0.\n");
								printf("Re-Enter product %d quantity:" , i+1);
								scanf("%d", &productList[i].quantity);
							}

							//Price
							printf("Enter product %d price($):" , i+1);
							scanf("%f", &productList[i].price);
							clr_buff();
							while(productList[i].price < 0){
								printf("Oops, the price must be larger than zero.\n");
								printf("Reenter product %d price($):" , i+1);
								scanf("%f", &productList[i].price);clr_buff();
							}
							printf("Do you want to add more products? (Y or N) : ");
							scanf("%c", &ch);
						
					}
					printf("DONE!\n");
					clr_buff();
				} break;
			
			case '3':
				{	
				printf("#\tProductName\tPrice\tQty\n");
				if (product_num == 0)
					printf("There are no product current available in store. Plase enter 1 to input!\n");
				else{	
					for (i=0; i < product_num; i++){
						printf("%d\t%s\t$%.1f\t%d\n", productList[i].productID , productList[i].productName , productList[i].price , productList[i].quantity );
					}
				} 
				clr_buff();
				} break;
			
			case '4':
				{
				clr_buff();
				printf("Enter a name you want to search: ");
				gets(searchProductName);
				int found = 0;
				printf("\n#\tProductName\tPrice\tQty\n");

				for (i=0; i < product_num; i++){
					if(strcmp(productList[i].productName, searchProductName) == 0){
						printf("%d\t%s\t$%.1f\t%d\n", productList[i].productID , productList[i].productName , productList[i].price , productList[i].quantity );
						found ++;
					}
				}

				if (found == 0){
					printf("Sorry, we cant find '%s' :(\nLeading back to homepage...\n", searchProductName);
				}else{
					printf(" Yoohoo! We found %d of your keyword '%s'.\nLeading back to homepage...\n", found, searchProductName);
				}

				} break;
				
			case '5':
				{
					//Product Store
					printf("#\tProductName\tPrice\tQty\n");
					if (product_num == 0)
						printf("There are no product current available in store. Please enter 1 to input!\n");
					else{	
						for (i=0; i < product_num; i++){
							printf("%d\t%s\t$%.1f\t%d\n", productList[i].productID , productList[i].productName , productList[i].price , productList[i].quantity );
						}
					} 
					printf("\n* * * *\n");
					printf("Enter ID of product you want to buy :");
					scanf("%d", &s_productID);
					int findProduct = 0;
					for (int i = 0; i < product_num; ++i){
						if (productList[i].productID == s_productID)
						{
							findProduct++;
						}
					}
					if (findProduct == 0){
						printf("Sorry :( we cant find your id, please re-buy.\n");
					}else{
						printf("Do you mean this product '%s' (Y or N) ? : ", productList[s_productID].productName);
						clr_buff();
						scanf("%c", &ch);	
					}
					
					if(ch == 'Y' || ch == 'y'){
						printf("\nBuying product '%s'...\n", productList[s_productID].productName);
						printf("Enter the amount you want to buy: ");
						scanf("%d", &s_quantity);

						if(productList[s_productID].quantity < s_quantity){
							printf("Sorry :( we just have %d ish of this product left!\n", productList[s_productID].quantity);
							printf("Do you want to buy all of them (Y or N) : ");
							clr_buff();
							scanf("%c", &ch);
							if (ch == 'Y' || ch == 'y'){
								printf("Here you are!\n");
								s_total = productList[s_productID].quantity * productList[s_productID].price;
								productList[s_productID].quantity = 0;
								printf("You have to pay $%f\nThank ygou for buyin!\n", s_total);
								s_count++;
							}else{
								printf("Exiting program...\n");
							}
						}else{
							printf("Here you are!\n");
							s_total = s_quantity * productList[s_productID].price;
							productList[s_productID].quantity -= s_quantity;
							printf("You have to pay $%f\nThank you for buying!\n", s_total);
							s_count++;
						}
					}else{
						printf("Exiting program...\n");
					}
				clr_buff();
				} break;	

			case '6':
				{

				printf("\n Exit application!");
				}break;

			default:
			{
            	printf("\nYour choice is invalid. Please enter again!\n");
           		clr_buff();
            	}break;
		}
	}	
	while(choice!='6'); 
}