#include <tesseract/baseapi.h>
#include <tesseract/strngs.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Please specify the input image!" << std::endl;
        return -1;
    }

    const char* lang = "eng";
    const char* filename = argv[1];

    tesseract::TessBaseAPI tess;
    tess.Init(NULL, lang, tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

    FILE* fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        std::cout << "Cannot open " << filename << std::endl;
        return -1;
    }
    fclose(fin);

    STRING text;
    if (!tess.ProcessPages(filename, NULL, 0, &text))
    {
        std::cout << "Error during processing." << std::endl;
        return -1;
    }
    else
        std::cout << text.string() << std::endl;

    return 0;
}