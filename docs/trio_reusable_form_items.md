# Reusable family transformations

All33 family evolution/reversion items are now reusable. The six early items
that previously disappeared after successful use are Riko's Wand, Blue Brush,
Bijuu's Fish Toy, Bijuu's Cat Nip, Dad's Keys and Piece of Chicken. Their Bag
descriptions now say Reusable. Forward/reverse form rules remain unchanged.

Thirteen reusable transformation items stay in the ordinary Items pocket:
those six plus Green Pepper, Eel Sushi, Frozen Fish, Toxic Mouse, Mouse Toy,
Dog Bowl and Fetching Stick. The20 later costume/trial/garden/elemental items
stay protected Key Items. This retains existing save inventories without a
pocket migration. Prices, shops, gifts, quantities, held-item behavior, item
IDs, species/form rules and saved layouts retain their current definitions.
Previously consumed copies are not automatically restored.

The successful evolution callback now exempts all13 ordinary family items
from RemoveBagItem. Existing Key Items already bypass consumption. Ordinary
evolution stones still consume one on success; failed/ineligible/cancelled
uses retain their existing behavior. All three party-menu styles compile
the shared callback.

tools/forms/validate_reusability.py audits the33 items against the actual
consumption condition and compares historical metadata/form rules. The user
authorized100% battle run-off and round-trip Goldenrod/island testing hooks
remain in this build. Keep PR2 draft/unmerged. Rendered use/reversion and real
save/reload remain player tests.

Validation: all33 item classifications and the six updated descriptions pass;
ordinary stones, historical inventory metadata and species/form rules are
unchanged. RELEASE production build passed (32,728,296 linked bytes,
EWRAM255,432, padded32MiB). Existing parade/run-off ROM registrations pass.
