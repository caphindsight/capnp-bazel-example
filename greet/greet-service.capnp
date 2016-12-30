@0xc73d0d7d27c09f10;

interface GreetService {
    greet @0 (name: Text) -> (greeting: Text);
    rand @1 () -> (randVal: Int32);
}

