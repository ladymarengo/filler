echo "" > trace2

echo "\n---MAP02---\n"

echo "CHAMPELY"

echo "Nsamoilo against Champely map02\n" >> trace_map02
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/champely.filler > trace_champely1
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/champely.filler > trace_champely2
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/champely.filler > trace_champely3
grep "fin" trace_champely1 | tail -2 >> trace_map02
echo "1"
grep "fin" trace_champely2 | tail -2 >> trace_map02
echo "2"
grep "fin" trace_champely3 | tail -2 >> trace_map02
echo "3"
echo "" >> trace_map02


echo "ABANLIN"

echo "Nsamoilo against Abanlin map02\n" >> trace_map02
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/abanlin.filler > trace_abanlin1
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/abanlin.filler > trace_abanlin2
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/abanlin.filler > trace_abanlin3
grep "fin" trace_abanlin1 | tail -2 >> trace_map02
echo "1"
grep "fin" trace_abanlin2 | tail -2 >> trace_map02
echo "2"
grep "fin" trace_abanlin3 | tail -2 >> trace_map02
echo "3"
echo "" >> trace_map02

echo "HCAO"

echo "Nsamoilo against Hcao map02\n" >> trace_map02
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/hcao.filler > trace_hcao1
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/hcao.filler > trace_hcao2
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/hcao.filler > trace_hcao3
grep "fin" trace_hcao1 | tail -2 >> trace_map02
echo "1"
grep "fin" trace_hcao2 | tail -2 >> trace_map02
echo "2"
grep "fin" trace_hcao3 | tail -2 >> trace_map02
echo "3"
echo "" >> trace_map02

echo "GRATI"

echo "Nsamoilo against Grati map02\n" >> trace_map02
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/grati.filler > trace_grati1
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/grati.filler > trace_grati2
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/grati.filler > trace_grati3
grep "fin" trace_grati1 | tail -2 >> trace_map02
echo "1"
grep "fin" trace_grati2 | tail -2 >> trace_map02
echo "2"
grep "fin" trace_grati3 | tail -2 >> trace_map02
echo "3"
echo "" >> trace_map02

echo "CARLI"

echo "Nsamoilo against Carli map02\n" >> trace_map02
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/carli.filler > trace_carli1
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/carli.filler > trace_carli2
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/carli.filler > trace_carli3
grep "fin" trace_carli1 | tail -2 >> trace_map02
echo "1"
grep "fin" trace_carli2 | tail -2 >> trace_map02
echo "2"
grep "fin" trace_carli3 | tail -2 >> trace_map02
echo "3"
echo "" >> trace_map02

echo "SUPERJEANNOT"

echo "Nsamoilo against Superjeannot map02\n" >> trace_map02
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/superjeannot.filler > trace_superjeannot1
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/superjeannot.filler > trace_superjeannot2
./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map02 -p2 players/superjeannot.filler > trace_superjeannot3
grep "fin" trace_superjeannot1 | tail -2 >> trace_map02
echo "1"
grep "fin" trace_superjeannot2 | tail -2 >> trace_map02
echo "2"
grep "fin" trace_superjeannot3 | tail -2 >> trace_map02
echo "3"
echo "" >> trace_map02