import 'dart:io';

class Pos{
  int x, y, z;

  Pos(this.x, this.y, this.z);

  String toString() {
    return '(' + x.toString() + ',' + y.toString() + ',' + z.toString() + ')'; 
  }
}

List<int> p = [];

void main() {
  for(int i=0; i<4; i++) {
    String s = stdin.readLineSync();
    int x = int.parse(s.substring(3,s.indexOf(',')));
    print(x);
  }
}
