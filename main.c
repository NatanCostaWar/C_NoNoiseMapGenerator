#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv){
	srand(time(NULL));

	//Default loop variables:
	int i = 0;
	int j = 0;
	int a = 0;
	int b = 0;
	
	
	//Creating Map File
	FILE * file;
    file = fopen("c:\\Users\\natan\\Desktop\\map.txt","w");
	
	//Creating the Map
	int width= 100;
	int height = 60;
	
	char WATER  = '.';
	char GRASS = 'i';
	char SAND = 'T';
	char MOUNTAIN = 'M';
	char SNOW  = 'N';
	char SHALLOW  = 'R';
	

    printf("map width (standard: 100) (max: 1000): \n");
    scanf("%i", &width);
    printf("map width (standard: 100) (max: 1000): \n"); 
    scanf("%i", &height);

	char mapa [width][height];
	
	//Filling the map with water
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			mapa[i][j] = WATER;
		}
	}
	
	
	//Generating Initial Land Points
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			int x = rand() % 300;
			if(x < 4 && i>5 && i<width-5 && j>5 && j<height-5){
				mapa[i][j] = '1';
			}
		}
	}
		
	
	//Generating Lands From Initial Points
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j] == '1'){
				for(a=i-5;a<=i+5;a++){
					for(b=j-5;b<=j+5;b++){
						if(a == i && b == j){
						}else{
							int x = rand() % 100;
							if(x > 50){
								mapa[a][b]= GRASS;
							}	
						}	
					}
				}
			}
		}
	}
	
	//Removing Initial Land Points
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j] == '1'){
				mapa[i][j]=GRASS;
			}		
		}
	}
	
	
	//Filling Map Edges With Water
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(i < 3 || i>width-3 || j<3 || j>height-3){
				mapa[i][j]=WATER;
			}		
		}
	}
	
	//Filling with Land Water points Btween Land Points
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			//WATER ENTRE DUAS GRASSS
			if(mapa[i][j] == GRASS && mapa[i+1][j] == WATER && mapa[i+2][j] == GRASS){
				mapa[i+1][j] = GRASS;
			}
			if(mapa[i][j] == GRASS && mapa[i-1][j] == WATER && mapa[i-2][j] == GRASS){
				mapa[i-1][j] = GRASS;
			}
			if(mapa[i][j] == GRASS && mapa[i][j+1] == WATER && mapa[i][j+2] == GRASS){
				mapa[i][j+1] = GRASS;
			}
			if(mapa[i][j] == GRASS && mapa[i][j-1] == WATER && mapa[i][j-2] == GRASS){
				mapa[i][j-1] = GRASS;
			}
			//DUAS WATERS ENTRE DUAS GRASSS
			if(mapa[i][j] == GRASS && mapa[i+1][j] == WATER && mapa[i+2][j] == WATER && mapa[i+3][j] == GRASS){
				mapa[i+1][j] = GRASS;
				mapa[i+2][j] = GRASS;
			}if(mapa[i][j] == GRASS && mapa[i-1][j] == WATER && mapa[i-2][j] == WATER && mapa[i-3][j] == GRASS){
				mapa[i-1][j] = GRASS;
				mapa[i-2][j] = GRASS;
			}if(mapa[i][j] == GRASS && mapa[i][j+1] == WATER && mapa[i][j+2] == WATER && mapa[i][j+3] == GRASS){
				mapa[i][j+1] = GRASS;
				mapa[i][j+2] = GRASS;
			}if(mapa[i][j] == GRASS && mapa[i][j-1] == WATER && mapa[i][j-2] == WATER && mapa[i][j-3] == GRASS){
				mapa[i][j+1] = GRASS;
				mapa[i][j+2] = GRASS;
			}
			
			
		}
	}
	
	//Generating beaches
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j] == WATER && mapa[i+1][j] == GRASS && mapa[i+2][j] == GRASS && mapa[i+3][j]==GRASS){
				mapa[i+1][j] = SAND;
				
			}if(mapa[i][j] == WATER && mapa[i-1][j] == GRASS && mapa[i-2][j] == GRASS && mapa[i-3][j]==GRASS){
				mapa[i-1][j] = SAND;
				
			}if(mapa[i][j] == WATER && mapa[i][j+1] == GRASS && mapa[i][j+2] == GRASS && mapa[i][j+3]==GRASS){
				mapa[i][j+1] = SAND;
				
			}if(mapa[i][j] == WATER && mapa[i][j-1] == GRASS && mapa[i][j-2] == GRASS && mapa[i][j-3]==GRASS){
				mapa[i][j-1] = SAND;
				
			}
				
		}
	}
	
	
	
	//Generating shallow
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j] == SAND && mapa[i+1][j] == WATER && mapa[i+2][j] == WATER){
				mapa[i+1][j] = SHALLOW;
				mapa[i+2][j] = SHALLOW;
			}
			if(mapa[i][j] == SAND && mapa[i-1][j] == WATER && mapa[i-2][j] == WATER){
				mapa[i-1][j] = SHALLOW;
				mapa[i-2][j] = SHALLOW;
			}
			if(mapa[i][j] == SAND && mapa[i][j+1] == WATER && mapa[i][j+2] == WATER){
				mapa[i][j+1] = SHALLOW;
				mapa[i][j+2] = SHALLOW;
			}
			if(mapa[i][j] == SAND && mapa[i][j-1] == WATER && mapa[i][j-2] == WATER){
				mapa[i][j-1] = SHALLOW;
				mapa[i][j-2] = SHALLOW;
			}
			
		}
	}
	
	
	
	//Generating Mountains
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j] == GRASS){
				int quant = 0;
				int start = 0;
				for(a=i;a<width;a++){
					if(mapa[a][j]==GRASS){
						quant++;
						if(mapa[a-1][j]!=GRASS){
							start=a;
						}
					}else{
						if(quant>8){
							for(b=4;b<quant-4;b++){
								mapa[start+b][j] = MOUNTAIN;
							}
						}
						quant=0;
					}
				}	
			}
				
		}
	}
	
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j]==SAND && mapa[i][j+1]==MOUNTAIN || mapa[i][j]==SAND && mapa[i][j+2]==MOUNTAIN || mapa[i][j]==SAND && mapa[i][j+3]==MOUNTAIN || mapa[i][j]==SAND && mapa[i][j+4]==MOUNTAIN){
				mapa[i][j+1]=GRASS;
				mapa[i][j+2]=GRASS;
				mapa[i][j+3]=GRASS;
				mapa[i][j+4]=GRASS;
			}
			if(mapa[i][j]==SAND && mapa[i][j-1]==MOUNTAIN || mapa[i][j]==SAND && mapa[i][j-2]==MOUNTAIN || mapa[i][j]==SAND && mapa[i][j-3]==MOUNTAIN || mapa[i][j]==SAND && mapa[i][j-4]==MOUNTAIN){
				mapa[i][j-1]=GRASS;
				mapa[i][j-2]=GRASS;
				mapa[i][j-3]=GRASS;
				mapa[i][j-4]=GRASS;
			}
		}
	}
	
	
	//Generating Snow
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j] == MOUNTAIN){
				int quant=0;
				int start=0;
				for(a=i;a<width;a++){
					if(mapa[a][j]==MOUNTAIN){
						quant++;
						if(mapa[a-1][j]!=MOUNTAIN){
							start=a;
						}
					}else{
						if(quant>10){
							for(b=5;b<quant-5;b++){
								mapa[start+b][j] = SNOW;
							}
						}
						quant=0;
					}
				}	
			}
				
		}
	}
	
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j]==GRASS && mapa[i][j+1]==SNOW || mapa[i][j]==GRASS && mapa[i][j+2]==SNOW || mapa[i][j]==GRASS && mapa[i][j+3]==SNOW || mapa[i][j]==GRASS && mapa[i][j+4]==SNOW || mapa[i][j]==GRASS && mapa[i][j+5]==SNOW){
				mapa[i][j+1]=MOUNTAIN;
				mapa[i][j+2]=MOUNTAIN;
				mapa[i][j+3]=MOUNTAIN;
				mapa[i][j+4]=MOUNTAIN;
				mapa[i][j+5]=MOUNTAIN;
			}
			if(mapa[i][j]==GRASS && mapa[i][j-1]==SNOW || mapa[i][j]==GRASS && mapa[i][j-2]==SNOW || mapa[i][j]==GRASS && mapa[i][j-3]==SNOW || mapa[i][j]==GRASS && mapa[i][j-4]==SNOW || mapa[i][j]==GRASS && mapa[i][j-5]==SNOW){
				mapa[i][j-1]=MOUNTAIN;
				mapa[i][j-2]=MOUNTAIN;
				mapa[i][j-3]=MOUNTAIN;
				mapa[i][j-4]=MOUNTAIN;
				mapa[i][j-5]=MOUNTAIN;
			}
		}
	}
	
	
	//Putting The Map In Archive
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			fprintf(file, "%c",mapa[i][j]);
		}
		fprintf(file, "\n");
	}
		
  	//Creating PPM image of map
  	FILE * file_img;
    file_img = fopen("c:\\Users\\natan\\Desktop\\map.ppm","w");
	//PPM Head Config
	fprintf (file_img, "P3\n");
    fprintf (file_img, "%i %i\n", width, height);
    fprintf (file_img, "255\n");
	 
	//Generating PPM Image
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			
			if(mapa[i][j] == GRASS){
				int x = rand() % 100;
				if(x>50){
					fprintf(file_img, "86",3);
					fprintf(file_img, " ",1);
					fprintf(file_img, "150",3);
					fprintf(file_img, " ",1);
					fprintf(file_img, "116",3);
					fprintf(file_img, " ",1);
				}else{
					fprintf(file_img, "173",3);
					fprintf(file_img, " ",1);
					fprintf(file_img, "220",3);
					fprintf(file_img, " ",1);
					fprintf(file_img, "176",3);
					fprintf(file_img, " ",1);
				}
			}else if(mapa[i][j] == WATER){
				fprintf(file_img, "14",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "106",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "131",3);
				fprintf(file_img, " ",1);
			}else if(mapa[i][j] == SHALLOW){
				fprintf(file_img, "179",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "228",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "207",3);
				fprintf(file_img, " ",1);
			}else if(mapa[i][j] == SAND){
				fprintf(file_img, "229",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "229",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "179",3);
				fprintf(file_img, " ",1);
			}else if(mapa[i][j] == MOUNTAIN){
				fprintf(file_img, "61",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "58",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "51",3);
				fprintf(file_img, " ",1);
			}else if(mapa[i][j] == SNOW){
				fprintf(file_img, "207",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "207",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "207",3);
				fprintf(file_img, " ",1);
			}else{
				fprintf(file_img, "230",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "226",3);
				fprintf(file_img, " ",1);
				fprintf(file_img, "214",3);
				fprintf(file_img, " ",1);
			}
			
		}
		fprintf(file_img, "\n",1);
	}



fclose(file_img);
fclose(file);

return 0;
}
