from algoritmos import (
    metodo_diferencas_finitas_pvc1,
    calcular_erros_pvc1,
    resolver_pvc2,
)


def main():
    N = 8
    y_aprox = metodo_diferencas_finitas_pvc1(N)
    x_values, y_exato, erros_relativos = calcular_erros_pvc1(y_aprox, N)

    print("Método de Diferenças Finitas - PVC1\n")
    print(f"{'x':>8} {'y_aprox':>12} {'y_exato':>12} {'Erro Relativo (%)':>20}")
    for i in range(N - 1):
        print(
            f"{x_values[i]:8.4f} {y_aprox[i + 1]:12.8f} {y_exato[i]:12.8f} {erros_relativos[i] * 100:20.8f}"
        )

    print("\n------------------------------------\n")
    print("Método de Diferenças Finitas - PVC2")
    u_aprox = resolver_pvc2(N)

    print(f"{'y':>5} {'u_aprox':>15}")
    print("----------------------------------")

    for i in range((N - 1) ** 2):
        print("|  u{:02d}  |   {:.8f}           |".format(i + 1, u_aprox[i]))

    print("----------------------------------")


if __name__ == "__main__":
    main()
