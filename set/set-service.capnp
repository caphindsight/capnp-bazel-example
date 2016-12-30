@0xf248427e2cd6b8f7;

interface SetService {
    contains @0 (x :Int32) -> (val :Bool);
    insert @1 (x: Int32) -> (res: Bool);
    remove @2 (x: Int32) -> (res: Bool);
}
