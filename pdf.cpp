#include "pdf.hpp"
#include <podofo/podofo.h>

using namespace PoDoFo;

Pdf::Pdf()
{
}

void Pdf::merge(std::vector<std::string> &files, std::string &outputName) {
    PdfMemDocument out;

    for (auto &file : files) {
        PdfMemDocument src;
        src.Load(file.c_str());
        out.GetPages().AppendDocumentPages(src);
    }

    out.Save(outputName.c_str());
}
