    // created by : alisharify
    //Do not copy code

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

int main(int argc, char *argv[])
{
    //check for 2 arguments
    if (argc != 2)
    {
        printf("Usage Error: ./program-name <filename>\n");
        return 1;
    }
    // open user input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Usage Error: Cant open < %s > file\n", argv[1]);
        return 1;
    }
    /* 0xff 0xd8 0xff
    0xe0 to 0xef */
    byte buffer_pic[512];

    //counter for name of file
    int counter = 0;

    int jpg_cc = 0;
    int jpg_one = 1;
    int flag = 0;

    //global file pointer
    FILE *pic_G = NULL;

    //read card file
    while (fread(buffer_pic, sizeof(byte), 512, input))
    {
        //check for 3 first byte for jpeg
        if (buffer_pic[0] == 0xff && buffer_pic[1] == 0xd8 && buffer_pic[2] == 0xff && (buffer_pic[3] & 0xf0) == 0xe0)
        {

            if (jpg_one == 0)
            {
                fclose(pic_G);
            }
            flag = 1;
            jpg_cc = 1;
        }
        else
        {
            jpg_cc = 0;
        }

        // check for new pic
        if (jpg_cc == 1)
        {
            // in here we definatly find a pic so we update jpg_one 
            //in next round we shoud close curccly file
            jpg_one = 0;

            //generate file name
            char filename[7];
            sprintf(filename, "%03i.jpg", counter);
            counter++;

            //open out put file
            pic_G = fopen(filename, "w");
            if (pic_G == NULL)
            {
                return 1;
            }
        }

        // in here with flag we just write to new file
        if (flag == 1)
        {
            fwrite(buffer_pic, sizeof(byte), 512, pic);
        }

    }

    //close files
    fclose(input);
    fclose(pic_G);
    return 0;