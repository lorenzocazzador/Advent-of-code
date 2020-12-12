import 'dart:collection';
import 'dart:io';

Map<String,List<String>> m = {};

main() {
  while(true) {
    String s = stdin.readLineSync();

    if(s == null || s == '')
      break;

    List<String> l = s.split(')');

    if(!m.containsKey(l[0])) {
      m[l[0]] = [];
    }
    m[l[0]].add(l[1]);
  }

  Queue<List<dynamic>> q = Queue();
  int res = 0;
  q.add(['COM',0]);
  while(q.isNotEmpty) {
    List<dynamic> s = q.removeFirst();
    res += s[1];

    //print('s --> ${s.toString()}');
    if(m.containsKey(s[0])) {
      for(String x in m[s[0].toString()]) {
        q.add([x, s[1]+1]);
      }
    }
  }
  print('res --> $res');
}
