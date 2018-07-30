#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dir.h>

FILE *file;
char file_dec[10000], file_dec_all[10000];
char txt_crt[10000], txt_crt_ext[10];
int STR_YEAR=1960, STR_DAY=7;
int day, year_s, year_e;

void file_CRT();
void file_CRT1();
void CREAT_TXT_FILE();
int VALID_DATE();
int COUNT_DAY();
void TAKE_START_N_END();
void FILE_PRINT();

int main()
{
    char d[3];
    file_CRT();

A:
    CREAT_TXT_FILE();
    TAKE_START_N_END();
    FILE_PRINT();
    getchar();

B:
    printf("\nWANT TO CREAT ANOTHER FILE(Y/N):  ");
    scanf("%s", d);

    if(d[0]=='Y')
    {
        getchar();
        goto A;
    }
    else if(d[0]=='N')
    {
        return 0;
    }
    else
    {
        getchar();
        printf("WRONG INPUT\n");
        goto B;
    }

}

///******************************************************************************************************FOLDER CREAT
void file_CRT()
{
    char dccc[3];

AA:
    printf("Enter Path:  ");
    gets(file_dec);

CHEAKING:
    strcpy(file_dec_all, file_dec);
    strcat(file_dec_all, "\\text.txt");

    file=fopen(file_dec_all, "w");
    if(!file)
    {
        printf("No Folder Found...\nWant To Creat New Folder? (Y/N):  ");
AAA:
        scanf("%s", dccc);
        switch (dccc[0])
        {
        case 'Y':
            file_CRT1();
            goto CHEAKING;
            break;

        case 'N':
            getchar();
            goto AA;
            break;

        default:
            printf("Wrong Input. Press Y to creat new folder, press N to re-enter path:  ");
            goto AAA;
        }
    }

    fclose(file);
    remove(file_dec_all);
}
void file_CRT1()
{
    int check;

    check=mkdir(file_dec);

    getchar();

    if(!check)
        printf("Directory created\n");
    else
        printf("Unable to create directory\n");
}
///############################################################################################################

///*********************************************************************************************************CREAT TXT FILE
void CREAT_TXT_FILE()
{
    printf("Enter File Name:  ");
    gets(txt_crt);

    printf("Enter Extension: ");
    gets(txt_crt_ext);

    strcpy(file_dec_all, file_dec);
    strcat(file_dec_all, "\\");
    strcat(file_dec_all, txt_crt);
    strcat(file_dec_all, txt_crt_ext);

    file=fopen(file_dec_all, "w");
}
///############################################################################################################

///*********************************************************************************************************TAKE_START_N_END n VALID_DATE n COUNT_DAY
void TAKE_START_N_END()
{
    printf("ENTER STARTING YEAR: "), scanf("%d", &year_s);
    printf("ENTER ENDINGING YEAR: "), scanf("%d", &year_e);

    if(year_s<STR_YEAR || year_s>=year_e) printf("wrong input\nYear Start From %04d\n", STR_YEAR), TAKE_START_N_END();
    COUNT_DAY();
}
int VALID_DATE(int year1, int month1, int date1)
{
    if(year1%4!=0 && month1==2 && date1>28) return 0;

    if(year1%4==0 && year1%100==0 && year1%400!=0 && month1==2 && date1>28) return 0;

    if(month1==2 && date1>29) return 0;

    if((month1==2 || month1==4 || month1==6 || month1==9 || month1==11) && date1==31) return 0;

	return 1;
}
int COUNT_DAY()
{
	int dcd, mcd, ycd;

	for(ycd=STR_YEAR; ycd<=year_s; ycd++)
		for(mcd=1; mcd<=12; mcd++)
			for(dcd=1; dcd<=31; dcd++)
			{
				if(VALID_DATE(ycd, mcd, dcd))
				{
					if(dcd==1 && mcd==1 && ycd==STR_YEAR) day=STR_DAY;
					if(ycd==year_s && mcd==1 && dcd==1) return 0;

					day=day+1;
					if(day>7) day=1;
				}
			}
}
///############################################################################################################FILE_PRINT
void FILE_PRINT()
{
    int yfp, mfp, dfp, ddfp;

    for(yfp=year_s; yfp<=year_e; yfp++)
    {
        fprintf(file, "\n\n**************************************%d***************************************\n\n", yfp);
        for(mfp=1; mfp<=12; mfp++)
        {
            fprintf(file, "\n---------------------------%d-%02d--------------------------------\nSAT\tSUN\tMON\tTUE\tWED\tTHU\tFRI\n", yfp, mfp);
            for(ddfp=1; ddfp<day; ddfp++)
            {
                fprintf(file, "\t");
            }

            for(dfp=1; dfp<=31; dfp++)
                if(VALID_DATE(yfp, mfp, dfp))
                {
                    fprintf(file, "%3d\t", dfp);

                    day=day+1;
					if(day>7) day=1, fprintf(file, "\n");
                }
        }
    }
    fclose(file);
}
