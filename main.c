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
	int x = 0;
	
	//Creating the Map
	int width= 100;
	int height = 60;
	
	
	//Mutable Variables and Configurations:
	#define WATER '.'
	#define GRASS 'i'
	#define SAND  'T'
	#define MOUNTAIN 'M'
	#define SNOW 'N'
	#define SHALLOW 'R'

	int generate_txt = 1;
	int generate_image = 1;

	int map_borders = 8;
	int land_percentage = 15; //max: 1000
	int land_generation_size = 5; //max: map_borders size
	int land_hardness = 30; //max: 100
	int mountain_distance = 10; //min: 2, only even numbers
	int snow_distance = 10; //min: 2, only even numbers


    printf("map width (standard: 100) (max: 1000): \n");
    scanf("%i", &width);
    printf("map width (standard: 60) (max: 1000): \n"); 
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
			int x = rand() % 1000;
			if(x < land_percentage && i>map_borders && i<width-(map_borders+1) && j>map_borders && j<height-(map_borders+1)){
				mapa[i][j] = '1';
			}
		}
	}
		
	
	//Generating Lands From Initial Points
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(mapa[i][j] == '1'){
				for(a=i-land_generation_size;a<=i+land_generation_size;a++){
					for(b=j-land_generation_size;b<=j+land_generation_size;b++){
						if(a == i && b == j){
						}else{
							int x = rand() % 100;
							if(x < land_hardness){
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
	
	//Filling with Land Water points Btween Land Points
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			//WATER btween two GRASSS
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
			//two WATERS btween two GRASSS
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
			if(mapa[i][j] == WATER && mapa[i+1][j+1] == SAND || mapa[i][j] == WATER && mapa[i-1][j-1] == SAND || mapa[i][j] == WATER && mapa[i+1][j-1] == SAND || mapa[i][j] == WATER && mapa[i-1][j+1] == SAND){
				mapa[i][j] = SHALLOW;
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
						if(quant>mountain_distance){
							for(b=(int)mountain_distance;b<quant-((int)(mountain_distance/2));b++){
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
						if(quant>snow_distance){
							for(b=(int)(snow_distance/2);b<quant-((int)(snow_distance/2));b++){
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
	
	
	//Creating Map File
	if (generate_txt == 1)
	{
		FILE * file;
	    file = fopen("map.txt","w");
		for(j=0;j<height;j++){
			for(i=0;i<width;i++){
				fprintf(file, "%c",mapa[i][j]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}
	
	if (generate_image == 1)
	{
		//Creating PPM image of map
	  	FILE * file_img;
	    file_img = fopen("map.ppm","w");
		//PPM Head Config
		fprintf (file_img, "P3\n");
	    fprintf (file_img, "%i %i\n", width, height);
	    fprintf (file_img, "255\n");
		 
		//Generating PPM Image
		for(j=0;j<height;j++){
			for(i=0;i<width;i++){

				switch(mapa[i][j]){
					case GRASS:
						x = rand() % 100;
						if(x>50){
							fprintf(file_img, "86 150 116 ", 12);
						}else{
							fprintf(file_img, "173 220 176 ", 12);
						}
						break;
					case WATER:
						fprintf(file_img, "14 106 131 ", 12);
						break;
					case SHALLOW:
						fprintf(file_img, "179 228 207 ", 12);
						break;
					case SAND:
						fprintf(file_img, "229 229 179 ", 12);
						break;
					case MOUNTAIN:
						fprintf(file_img, "61 58 51 ", 12);
						break;
					case SNOW:
						fprintf(file_img, "207 207 207 ", 12);
						break;
					default:
						fprintf(file_img, "230 226 214 ", 12);
						break;
				
				}
				
			}
			fprintf(file_img, "\n",1);
		}
		fclose(file_img);
	}
	

  	

return 0;
}
