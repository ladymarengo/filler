echo "" > trace_maps_00_01

echo "\n---MAP00---\n"

echo "CHAMPELY"

echo "Nsamoilo against Champely map00\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map00 -p2 players/champely.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "ABANLIN"

echo "Nsamoilo against Abanlin map00\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map00 -p2 players/abanlin.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "HCAO"

echo "Nsamoilo against Hcao map00\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map00 -p2 players/hcao.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "GRATI"

echo "Nsamoilo against Grati map00\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map00 -p2 players/grati.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "CARLI"

echo "Nsamoilo against Carli map00\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map00 -p2 players/carli.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "SUPERJEANNOT"

echo "Nsamoilo against Superjeannot map00\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map00 -p2 players/superjeannot.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "\n---MAP01---\n"

echo "CHAMPELY"

echo "Nsamoilo against Champely map01\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map01 -p2 players/champely.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "ABANLIN"

echo "Nsamoilo against Abanlin map01\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map01 -p2 players/abanlin.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "HCAO"

echo "Nsamoilo against Hcao map01\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map01 -p2 players/hcao.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "GRATI"

echo "Nsamoilo against Grati map01\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map01 -p2 players/grati.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "CARLI"

echo "Nsamoilo against Carli map01\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map01 -p2 players/carli.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done

echo "SUPERJEANNOT"

echo "Nsamoilo against Superjeannot map01\n" >> trace_maps_00_01
for i in {1..5}; do
   ./filler_vm -p1 ../../nsamoilo.filler -v -f maps/map01 -p2 players/superjeannot.filler > trace
   grep "fin" trace | tail -2 >> trace_maps_00_01
   echo "" >> trace_maps_00_01
done
cat trace_maps_00_01