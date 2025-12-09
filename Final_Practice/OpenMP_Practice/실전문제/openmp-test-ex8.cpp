sum     = 0.0;
max_err = 0.0;

for (i = 0; i < n; i++) {
    x   = i * h;
    u   = exact(x);
    v   = approx[i];

    sum += v;

    err = fabs(u - v);
    if (err > max_err)
        max_err = err;
}

avg = sum / n;

// Use OpenMP directives to make the loop(s) parallel, or explain why the code segment is less suitable for parallel execution.

/*
sum     = 0.0;
max_err = 0.0;

#pragma omp parallel for private(x, u, v, err) \
    reduction(+:sum) reduction(max:max_err)
for (i = 0; i < n; i++) {
    x   = i * h;
    u   = exact(x);
    v   = approx[i];

    sum += v;

    err = fabs(u - v);
    if (err > max_err)
        max_err = err;
}

avg = sum / n;
*/