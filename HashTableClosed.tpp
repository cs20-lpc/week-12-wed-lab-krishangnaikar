template <typename T>
int HashTableClosed<T>::insert(const T& key)
{
    if (N >= M) {
        throw overflow_error("Hash table is full");
    }

    int probes = 0;

    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        if (!occupied[index]) {
            table[index] = key;
            occupied[index] = true;
            N++;
            return probes;
        }

        // optional: avoid inserting duplicates twice
        if (table[index] == key) {
            return probes;
        }
    }

    throw overflow_error("No empty slot found");
}

template <typename T>
pair<bool, int> HashTableClosed<T>::search(const T& key) const
{
    int probes = 0;

    for (int i = 0; i < M; i++) {
        int index = probeIndex(key, i);
        probes++;

        if (!occupied[index]) {
            return {false, probes};
        }

        if (table[index] == key) {
            return {true, probes};
        }
    }

    return {false, probes};
}