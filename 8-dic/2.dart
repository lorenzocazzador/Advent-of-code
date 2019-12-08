import 'dart:io';

int width = 25;
int high = 6;

main() async {
  String l = await File('in').readAsString();
  //String l = stdin.readLineSync();

  int layerLength = width*high;
  List<String> img = List(layerLength);
  img.fillRange(0, layerLength, '2');

  for(int i=0; i<l.length-1; i++) {
    int ind = i % layerLength;

    if(img[ind] == '2')
      img[ind] = l[i];
  }

  String s = '';
  for(int i=0; i<img.length; i++) {
    s += (img[i] == '1' ? '#' : ' ');
    if( (i+1) % width == 0) {
      print(s);
      s = '';
    }
  }

}