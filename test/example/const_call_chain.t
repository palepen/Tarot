fn add2(x: number): number {
    return x + 2;
}
fn getFive(): number {
    return add2(3);
}
fn main(): void {
    println(getFive());
}
