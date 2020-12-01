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
  List<Chemical> chemicals;

  MapKey(this.qOutput, this.chemicals);
}

Map<String, MapKey> m = {};
Map<String, int> disp = {};

int solve(int q, String n) {
  if(n == 'ORE')
    return q;
  else {
    MapKey tmp = m[n];

    int v = q ~/ tmp.qOutput;
    if(q % tmp.qOutput != 0) v++;

    int res = 0;
    for(Chemical c in tmp.chemicals) {
      int q_tmp = c.quantity*v;
      if(disp.containsKey(c.name)) {
        int d = disp[c.name];
        disp[c.name] = (d <= q_tmp ? 0 : d-q_tmp);  
        q_tmp -= d;
      } 
      
      if(q_tmp > 0)
        res += solve(q_tmp, c.name);
    }

    if(!disp.containsKey(n))
      disp[n] = 0;

    if(q % tmp.qOutput > 0)
      disp[n] += tmp.qOutput - (q % tmp.qOutput);

    //print('n: $n res: $res disp: ${disp[n]}');
    return res;
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

  int x = 7863863;
  int res = solve(x, 'FUEL');
  print('x: $x res --> $res');
}