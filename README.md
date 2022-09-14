![GitHub release (latest by date)](https://img.shields.io/github/v/release/ImageProcessing-ElectronicPublications/jpeg2pdf)
![GitHub Release Date](https://img.shields.io/github/release-date/ImageProcessing-ElectronicPublications/jpeg2pdf)
![GitHub repo size](https://img.shields.io/github/repo-size/ImageProcessing-ElectronicPublications/jpeg2pdf)
![GitHub all releases](https://img.shields.io/github/downloads/ImageProcessing-ElectronicPublications/jpeg2pdf/total)
![GitHub](https://img.shields.io/github/license/ImageProcessing-ElectronicPublications/jpeg2pdf)

# jpeg2pdf

Cross-platform command-line tool for creation of PDF documents from scans/photos of pages in JPEG (.jpg) format and the lightest weight ANSI C library to put multiple JPEG files into one PDF file.

### HOW TO USE

1. Create PDF 'document.pdf' from all JPEG files in current directory:
```sh
    jpeg2pdf *.jpg -o document.pdf
```

2. Create PDF 'scans.pdf' with: page size determined by maximum image size, page orientation forced to 'portrait', preserve the original dpi of images (don't scale), crop the height of each page at image borders (yields good results for scans with white background and correct dpi)
```sh
    jpeg2pdf -o scans.pdf -p auto -n portrait -z none -r height *.jpg
```

3. Create PDF 'from_photos.pdf' with: A5 paper size, landscape orientation, fit the width of images (fw -- fit width), crop the height of each page (works well for properly cropped photos of A5 pages in landscape with unknown/wrong dpi and approximately correct widths)
```sh
    jpeg2pdf -o from_photos.pdf -p A5 -n landscape -z fw -r height *.jpg
```

4. It is possible to specify the title, author, subject, keyword, and creator of produced PDF document with switches `-t`, `-a`, `-s`, `-k`, `-c`:
```sh
    jpeg2pdf -o doc.pdf -t "The Title of PDF" -a Andrew -c jpeg2pdf *.jpg
```

### HOW TO COMPILE AND INSTALL

```sh
make && make install
```
compiles and installs `jpeg2pdf` to `/usr/local/bin`.

### PROJECT HOME

http://sourceforge.net/projects/jpeg2pdf/

