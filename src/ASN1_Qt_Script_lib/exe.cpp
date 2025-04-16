#include <iostream>
#include <QCoreApplication>

#include "Script.h"

const QString script1 = R"(
  var defA = new BitStringASN1('def A');
  defA.setBitStringValue('11');

  var A = new BitStringASN1('A', '', false, false, defA);
  A.registerGrammar();

  var s = A.getBitStringValue();
)";

const QString script2 = R"(
  var A = new UTCTimeASN1('T');

  A.setUTCTimeValue("9001031702+0100");
  var s1 = A.getUTCTimeValue();

  A.setUTCTimeValue(91, 3, 11, 10, 30, 0, UTCTimeASN1.Plus, 1, 0);
  var s2 = A.getUTCTimeValue();

  A.registerGrammar();
)";

const QString script3 = R"(
  function MakeSeq1() {
    var a1 = new BitStringASN1('bitstring a', '0A');
    var b1 = new BitStringASN1('bitstring b', '0B', true, true);
    var c1 = new BitStringASN1('bitstring c', '0C');
    return [a1, b1, c1];
  }

  var seq1 = new SequenceASN1(MakeSeq1(), 'Sequence 1', 'AA');

  seq1.getObjectAt(0).setBitStringValue('1010');
  seq1.getObjectAt(1).setBitStringValue('1000');
  seq1.getObjectAt(1).setIgnoredByUser(true);
  seq1.getObjectAt(2).setBitStringValue('001');

  seq1.registerGrammar();
)";

int main(int argc, char const* argv[])
{
  std::cout << "/* start */" << std::endl;
  QCoreApplication app(argc, const_cast<char**>(argv));
  QString error;
  bool res = true;

  if (true) {
    QJSEngine* eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script1, error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cBitString;
    res &= eng->globalObject().property("s").toString().toStdString() == "";

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "0300";
  }

  if (false) {
    QJSEngine* eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script2, error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cUTCTime;
    res &= eng->globalObject().property("s1").toString().toStdString() == "9001031702+0100";
    res &= eng->globalObject().property("s2").toString().toStdString() == "9103111030+0100";

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "170F393130333131313033302B30313030";
  }

  if (false) {
    QJSEngine* eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script3, error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cSequence;

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "AA080A0204A00C020520";
  }

  ClearGrammar();
  res &= ScriptMemoryCheck();

  std::cout << "/* done */ " << (res ? "OK" : "NOT OK !!!") << std::endl;
  return 0;
}
