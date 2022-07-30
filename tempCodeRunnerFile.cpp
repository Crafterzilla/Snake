    int tmp = 0;
    for (int i = 9; i > 0; i--) {
        tmp = array[i];
        array[i] = array[i - 1];
        array[i - 1] = tmp;
    }
    array[0] = 0;