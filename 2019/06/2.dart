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

    if(!m.containsKey(l[1])) {
      m[l[1]] = [];
    }
    m[l[1]].add(l[0]);
  }

  Queue<List<dynamic>> q = Queue();
  Set<String> visited = {};
  int res = 0;
  q.add(['YOU',0]);
  while(q.isNotEmpty) {
    List<dynamic> s = q.removeFirst();

    if(visited.contains(s[0]))
      continue;
    else visited.add(s[0]);

    //print('s --> ${s.toString()}');
    if(s[0] == 'SAN') {
      res = s[1] - 2;
      break;
    }

    if(m.containsKey(s[0])) {
      for(String x in m[s[0].toString()]) {
        q.add([x, s[1]+1]);
      }
    }
  }

  print('res --> $res');
}
