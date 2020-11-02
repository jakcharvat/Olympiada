//
//  main.swift
//  Olympiada
//
//  Created by Jakub Charvat on 31.10.2020.
//

import Foundation

run()

func run() {
    guard let firstLine = readLine()?.components(separatedBy: .whitespaces).compactMap(Int.init) else { return }
    let n = firstLine[0]
    let m = firstLine[1]
    let k = firstLine[2]
    
    guard let krizovatky = readLine()?.components(separatedBy: .whitespaces).enumerated().map({ (index, element) in
        return Krizovatka(id: index, podVodou: element == "1")
    }) else { return }
    
    (1...m).forEach { _ in
        guard let uliceDef = readLine()?.components(separatedBy: .whitespaces).compactMap(Int.init) else { return }
        let prvniKrizovatka = uliceDef[0]
        let druhaKrizovatka = uliceDef[1]
        krizovatky[prvniKrizovatka].pripojeneKrizovatky.insert(krizovatky[druhaKrizovatka])
        krizovatky[druhaKrizovatka].pripojeneKrizovatky.insert(krizovatky[prvniKrizovatka])
    }
    
    print(BFS.findRoute(krizovatky: krizovatky, k: k))
}



class Krizovatka: Hashable, CustomStringConvertible {
    let id: Int
    let podVodou: Bool
    var pripojeneKrizovatky: Set<Krizovatka> = []
    
    init(id: Int, podVodou: Bool = false) {
        self.id = id
        self.podVodou = podVodou
    }
    
    
    static func ==(lhs: Krizovatka, rhs: Krizovatka) -> Bool {
        return lhs.id == rhs.id
    }
    
    func hash(into hasher: inout Hasher) {
        hasher.combine(id)
    }
    
    
    var description: String {
        return "Krizovatka \(id) - pod vodou: \(podVodou) - pripojene: \(pripojeneKrizovatky.map(\.id))"
    }
}



struct BFSKrizovatka {
    let krizovatka: Krizovatka
    var cesta: [Krizovatka] = []
    var delka: Int = 0
}


struct BFS {
    static func findRoute(krizovatky: [Krizovatka], k: Int) -> String {
        var queue = [BFSKrizovatka(krizovatka: krizovatky.last!)]
        var visitedPoints = Set<Krizovatka>([krizovatky.last!])
        
        while !queue.isEmpty {
            let current = queue.removeFirst()
            
            let newDelka = current.delka + 1
            let newCesta = current.cesta + [current.krizovatka]
            
            for pripojena in current.krizovatka.pripojeneKrizovatky {
                if pripojena.id == 0 { return "\(newCesta.count)" }
                
                if visitedPoints.contains(pripojena) { continue }
                
                if !pripojena.podVodou || newDelka <= k {
                    queue.append(BFSKrizovatka(krizovatka: pripojena, cesta: newCesta, delka: newDelka))
                    visitedPoints.insert(pripojena)
                }
            }
        }
        
        return "-1"
    }
}
