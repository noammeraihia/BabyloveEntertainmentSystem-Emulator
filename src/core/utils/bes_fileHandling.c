#include "core/utils/bes_fileHandling.h"

besBinFile_t besLoadBinFile(const char *__filename)
{
    besBinFile_t _handle = {
        .bytes = {0x00},
        .fileSize = 0};

    FILE *_f = fopen(__filename, "rb");
    if (_f == NULL)
    {
        fprintf(stderr, "BES => \'%s\' opening has failed !\n", __filename);
        return (besBinFile_t){.bytes = {0xEA}, .fileSize = -1};
    }

    fseek(_f, 0, SEEK_END);
    _handle.fileSize = ftell(_f);
    fseek(_f, 0, SEEK_SET);

    for (int i = 0; !feof(_f); i++)
    {
        fread(&_handle.bytes[i], sizeof(unsigned char), 1, _f);
    }

    fclose(_f);

    return _handle;
}