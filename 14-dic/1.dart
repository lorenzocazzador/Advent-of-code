import 'dart:io';

class Chemical{
  int quantity;
  String name;

  Chemical(this.quantity, this.name);

  String toString() {
    return '[' + quantity.toString() + ',' + name + ']';
  }
}

Chemical parseChemical(String c) {
  return Chemical(int.parse(c.substring(0,c.indexOf(' '))), c.substring(c.indexOf(' ')+1));
}

class MapKey{
  int qOutput;
  List<Chemical> c;

  MapKey(this.qOutput, this.c);
}

Map<String, MapKey> m = {};

int solve(int q, String n) {
  if(n == 'ORE')
    return q;
  else {

  }
}

main() async {
  List<String> file = await File('14-dic/in').readAsLines();
  for(String s in file) {
    List<String> l = s.split(' => ');

    Chemical r = parseChemical(l[1]);
    List<Chemical> c = [];
    List<String> c_tmp = l[0].split(', ');
    for(String s1 in c_tmp)
      c.add(parseChemical(s1));

    //print('$c --> $r');
    m[r.name] = MapKey(r.quantity, c); 
  }

  int res = solve(1, 'FUEL');
  print('res --> $res');
}