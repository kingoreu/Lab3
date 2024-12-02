use std::io;

fn main() {
    // 행렬 크기 입력 받기
    let (rows, cols) = get_matrix_size();

    // 첫 번째 행렬 입력
    println!("Enter elements of the first matrix:");
    let matrix_a = read_matrix(rows, cols);

    // 두 번째 행렬 입력
    println!("Enter elements of the second matrix:");
    let matrix_b = read_matrix(rows, cols);

    // 두 행렬을 더하기
    let result_matrix = add_matrices(&matrix_a, &matrix_b, rows, cols);

    // 결과 출력
    println!("Resultant matrix after addition:");
    print_matrix(&result_matrix, rows, cols);
}

fn get_matrix_size() -> (usize, usize) {
    let mut input = String::new();
    println!("Enter the number of rows and columns (e.g., 2 3):");
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    (parts[0], parts[1])
}

fn read_matrix(rows: usize, cols: usize) -> Vec<Vec<i32>> {
    let mut matrix = Vec::new();
    for i in 0..rows {
        println!("Enter row {} ({} numbers separated by spaces):", i + 1, cols);
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let row: Vec<i32> = input
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        matrix.push(row);
    }
    matrix
}

fn add_matrices(
    matrix_a: &Vec<Vec<i32>>,
    matrix_b: &Vec<Vec<i32>>,
    rows: usize,
    cols: usize,
) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    for i in 0..rows {
        let mut row = Vec::new();
        for j in 0..cols {
            row.push(matrix_a[i][j] + matrix_b[i][j]);
        }
        result.push(row);
    }
    result
}

fn print_matrix(matrix: &Vec<Vec<i32>>, rows: usize, cols: usize) {
    for i in 0..rows {
        for j in 0..cols {
            print!("{} ", matrix[i][j]);
        }
        println!();
    }
}

